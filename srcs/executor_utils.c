/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:41:38 by farmoham          #+#    #+#             */
/*   Updated: 2026/02/28 15:58:00 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_fds(int *prev_fd, int pipe_fd[2], int has_next)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (has_next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

static void	setup_pipes(t_command *cmd, int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

static void	exec_external(t_command *cmd, t_shell *s)
{
	char	*path;
	char	**env_arr;

	env_arr = env_to_array(s->env);
	path = get_path(cmd->args[0], s->env);
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		free_args(env_arr);
		free_commands(s->cmds_head);
		free_env(s->env);
		exit(127);
	}
	execve(path, cmd->args, env_arr);
	perror("execve");
	free(path);
	free_args(env_arr);
	free_commands(s->cmds_head);
	free_env(s->env);
	exit(1);
}

static void	child_process(t_command *cmd, t_shell *s, int prev_fd,
		int pipe_fd[2])
{
	int	status;

	setup_pipes(cmd, prev_fd, pipe_fd);
	if (!apply_redirections(cmd))
	{
		free_commands(s->cmds_head);
		free_env(s->env);
		exit(1);
	}
	if (is_builtin(cmd->args[0]))
	{
		status = exec_builtin(cmd, s);
		free_commands(s->cmds_head);
		free_env(s->env);
		exit(status);
	}
	exec_external(cmd, s);
}

int	fork_process(t_command *cmd, t_shell *s, int prev_fd, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		init_signals_child();
		child_process(cmd, s, prev_fd, pipe_fd);
	}
	if (!cmd->next)
		s->last_pid = pid;
	return (0);
}
