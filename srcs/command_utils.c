#include "minishell.h"

/* ================= NEW COMMAND ================= */
t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

/* ================= ADD ARGUMENT ================= */
int	add_argument(t_command *cmd, char *value)
{
	char	**new_args;
	int		i;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (0);
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(value);
	if (!new_args[i])
		return (free(new_args), 0);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	cmd->cmd = cmd->args[0];
	return (1);
}

/* ================= ADD REDIRECTION ================= */
int	add_redirection(t_command *cmd,
	int type, char *file, int quoted)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->read_fd = -1;
	new->file = ft_strdup(file);
	if (!new->file)
		return (free(new), 0);
	new->type = type;
	new->quoted = quoted;
	new->next = NULL;
	if (!cmd->redirs)
	{
		cmd->redirs = new;
		return (1);
	}
	tmp = cmd->redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

/* ================= FREE REDIRS ================= */
void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

/* ================= FREE COMMANDS ================= */
void	free_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;
		i = 0;
		while (cmd->args && cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
		free_redirs(cmd->redirs);
		free(cmd);
		cmd = tmp;
	}
}