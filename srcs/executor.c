/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:58:55 by farmoham          #+#    #+#             */
/*   Updated: 2026/02/28 15:58:56 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	reset_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static int	exec_single(t_command *cmd, t_shell *s)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	status = 0;
	if (!apply_redirections(cmd))
		return (s->exit_status = 1, reset_fds(saved_stdin, saved_stdout), 0);
	if (!ft_strcmp(cmd->args[0], "exit"))
	{
		write(1, "exit\n", 5);
		if (cmd->args[1])
			status = ft_atoi(cmd->args[1]);
		free_commands(cmd);
		free_env(s->env);
		rl_clear_history();
		exit(status);
	}
	s->exit_status = exec_builtin(cmd, s);
	return (reset_fds(saved_stdin, saved_stdout), 1);
}

static void	exec_loop(t_command *cmds, t_shell *s)
{
	int	prev_fd;
	int	pipe_fd[2];

	prev_fd = -1;
	while (cmds)
	{
		if (cmds->next && pipe(pipe_fd) == -1)
			return ;
		if (fork_process(cmds, s, prev_fd, pipe_fd) == -1)
			return ;
		parent_fds(&prev_fd, pipe_fd, (cmds->next != NULL));
		cmds = cmds->next;
	}
}

void	executor(t_command *cmds, t_shell *s)
{
	if (!cmds)
		return ;
	s->cmds_head = cmds;
	if (is_single_builtin(cmds))
	{
		exec_single(cmds, s);
		s->cmds_head = NULL;
		return ;
	}
	s->last_pid = -1;
	init_signals_exec();
	exec_loop(cmds, s);
	wait_children(s);
	init_signals_interactive();
	s->cmds_head = NULL;
}
