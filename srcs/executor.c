#include "minishell.h"

static int	is_single_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (cmd->next != NULL)
		return (0);
	if (!is_builtin(cmd->args[0]))
		return (0);
	return (1);
}

static void reset_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO); 
	close(saved_stdin);
	close(saved_stdout);
}

static int exec_single(t_command *cmd, t_shell *s)
{
    int saved_stdin;
    int saved_stdout;
	int status;

    saved_stdin = dup(STDIN_FILENO);
    saved_stdout = dup(STDOUT_FILENO);
	status = 0;
	if (!apply_redirections(cmd))
    {    
		s->exit_status = 1;
		return (reset_fds(saved_stdin, saved_stdout), 0);
	}
    if (!ft_strcmp(cmd->args[0], "exit"))
    {
        write(1, "exit\n", 5);
        if (cmd->args[1])
			status = ft_atoi(cmd->args[1]);
		exit(status);
    }
    s->exit_status = exec_builtin(cmd, s);
	return (reset_fds(saved_stdin, saved_stdout), 1);
}

static void	exec_loop(t_command *cmds, t_shell *s)
{
	int		prev_fd;
	int		pipe_fd[2];

	prev_fd = -1;
	while (cmds)
	{
		if (cmds->next && pipe(pipe_fd) == -1) // if there is a next command, then creat a pipe
			return ;
		if (fork_process(cmds, s, prev_fd, pipe_fd) == -1) // we creat a process to the command
			return ;
		parent_fds(&prev_fd, pipe_fd, (cmds->next != NULL));
		cmds = cmds->next;
	}
}

void executor(t_command *cmds, t_shell *s)
{
	int     status;
	pid_t   pid;
	if (!cmds)
		return ;
	///check her if it is a single built in command, if yes, then no need to fork and we will directelly excute it
	if (is_single_builtin(cmds))
	{
		exec_single(cmds, s);
		return;
	}
	s->last_pid = -1;
	exec_loop(cmds, s);
	while ((pid = wait(&status)) > 0)
	{
		if (pid == s->last_pid)
		{
			if (WIFEXITED(status))
				s->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				s->exit_status = 128 + WTERMSIG(status);
		}
	} //main process will wait for all childrens, and one children will be created for each command
}