/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:00:28 by farmoham          #+#    #+#             */
/*   Updated: 2026/03/01 00:38:11 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_interrupt(int fd[2], t_shell *s, char *line)
{
	free(line);
	close(fd[0]);
	close(fd[1]);
	s->exit_status = 130;
	return (0);
}

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

static int	prepare_heredoc(t_redir *r, t_shell *s)
{
	int		fd[2];
	char	*line;

	g_sig = 0;
	if (pipe(fd) == -1)
		return (0);
	init_signals_heredoc();
	while (1)
	{
		line = readline("> ");
		if (g_sig == 130)
			return (init_signals_interactive(), heredoc_interrupt(fd, s, line));
		if (!line || ft_strcmp(line, r->file) == 0)
			break ;
		heredoc_write_line(r, s, fd[1], line);
	}
	init_signals_interactive();
	free(line);
	close(fd[1]);
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
