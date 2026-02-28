#include "minishell.h"

void	parent_fds(int *prev_fd, int pipe_fd[2], int has_next)
{
	if (*prev_fd != -1) //close the fd in parent process after a chiled is created and inhareted the fd already
		close(*prev_fd);
	if (has_next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0]; // we save the read end for the next command(process) to use
	}
}

static void	setup_pipes(t_command *cmd, int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1) // if there is a previous pipe
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next) // if there is a next pipe
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

static void	exec_external(t_command *cmd, t_env *env)
{
	char	*path;
	char	**env_arr;

	env_arr = env_to_array(env);
	path = get_path(cmd->args[0], env);
	if (!path)
	{
		printf("minishell: %s: command not found\n",
			cmd->args[0]);
		free_args(env_arr);
		exit(127);
	}
	execve(path, cmd->args, env_arr);
	perror("execve");
	free_args(env_arr);
	exit(1);
}

static void	child_process(t_command *cmd, t_shell *s,
		int prev_fd, int pipe_fd[2])
{
	setup_pipes(cmd, prev_fd, pipe_fd); // 1st we apply the pipes
	if (!apply_redirections(cmd))
		exit(1);      // 2nd we apply the redirection (so redirection will override pipes)
	if (is_builtin(cmd->args[0]))               // we check if the command is a built in, if not we use exceve
		exit(exec_builtin(cmd, s));  // finally child process exit()
	exec_external(cmd, s->env);
}

int	fork_process(t_command *cmd, t_shell *s,
		int prev_fd, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0) // faild
		return (-1);
	if (pid == 0) // child process
	{
		init_signals_exec();
		child_process(cmd, s, prev_fd, pipe_fd);
	}
    if (!cmd->next) // for parent
		s->last_pid = pid;
	return (0);
}