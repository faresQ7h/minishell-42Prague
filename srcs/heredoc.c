#include "minishell.h"

static int	prepare_heredoc(t_redir *r, t_shell *s)
{
	int		fd[2];
	char	*line;
	char	*tmp;

	if (pipe(fd) == -1)
		return (0);
	while (1)
	{
		line = readline("> ");
		if (g_sig == 130)
			return (close(fd[0]), close(fd[1]), s->exit_status = 130, 0);
		if (!line || ft_strcmp(line, r->file) == 0)
			break ;
		if (!r->quoted)
		{
			tmp = expand_string(line, s->env, s->exit_status);
			free(line);
			line = tmp;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
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
			if (r->type == T_HEREDOC &&
				!prepare_heredoc(r, shell))
				return (0);
			r = r->next;
		}
		cmds = cmds->next;
	}
	return (1);
}