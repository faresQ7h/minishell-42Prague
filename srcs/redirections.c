#include "minishell.h"

static int	redir_append(t_redir *r)
{
	int	fd;

	fd = open(r->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int	redir_output(t_redir *r)
{
	int	fd;

	fd = open(r->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int redir_input(t_redir *r)
{
    int fd;

    fd = open(r->file, O_RDONLY);
    if (fd < 0)
        return (0);
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (1);
}

static int handle_heredoc(t_redir *r)
{
    if (r->read_fd < 0)
        return (0);
    dup2(r->read_fd, STDIN_FILENO);
    close(r->read_fd);
    return (1);
}

int apply_redirections(t_command *cmd)
{
    t_redir *r;

    r = cmd->redirs;
    while (r)
    {
        if (r->type == T_REDIR_IN && !redir_input(r))
            return (0);
        else if (r->type == T_REDIR_OUT && !redir_output(r))
            return (0);
        else if (r->type == T_APPEND && !redir_append(r))
            return (0);
        else if (r->type == T_HEREDOC && !handle_heredoc(r))
			return (0);
        r = r->next;
    }
    return (1);
}