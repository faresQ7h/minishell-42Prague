/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:00:28 by farmoham          #+#    #+#             */
/*   Updated: 2026/03/01 02:22:02 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_write_line(t_redir *r, t_shell *s, int write_fd, char *line)
{
	char	*tmp;

	if (!r->quoted)
	{
		tmp = expand_string(line, s->env, s->exit_status);
		free(line);
		line = tmp;
	}
	write(write_fd, line, ft_strlen(line));
	write(write_fd, "\n", 1);
	free(line);
}

static void	heredoc_child(t_redir *r, t_shell *s, int fd[2])
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd[1]);
			exit(0);
		}
		if (ft_strcmp(line, r->file) == 0)
		{
			free(line);
			close(fd[1]);
			exit(0);
		}
		heredoc_write_line(r, s, fd[1], line);
	}
}

static int	prepare_heredoc(t_redir *r, t_shell *s)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (0);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
		heredoc_child(r, s, fd);
	close(fd[1]);
	waitpid(pid, &status, 0);
	init_signals_interactive();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd[0]);
		s->exit_status = 130;
		write(1, "\n", 1);
		return (0);
	}
	r->read_fd = fd[0];
	return (1);
}

int	process_heredocs(t_command *cmds, t_shell *shell)
{
	t_redir	*r;

	while (cmds)
	{
		r = cmds->redirs;
		while (r)
		{
			if (r->type == T_HEREDOC && !prepare_heredoc(r, shell))
				return (0);
			r = r->next;
		}
		cmds = cmds->next;
	}
	return (1);
}
