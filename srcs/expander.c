/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:59:47 by farmoham          #+#    #+#             */
/*   Updated: 2026/02/28 15:59:53 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ================= HANDLE CHAR ================= */

static void	handle_char(t_expand *e)
{
	if (e->str[e->i] == '\'' && !e->double_q)
		e->single = !e->single;
	else if (e->str[e->i] == '"' && !e->single)
		e->double_q = !e->double_q;
	else if (e->str[e->i] == '$' && !e->single)
		expand_variable(e);
	else
		e->result = ft_strjoin_char(e->result, e->str[e->i]);
}

/* ================= EXPAND STRING ================= */

char	*expand_string(char *str, t_env *env, int last_status)
{
	t_expand	e;

	e.str = str;
	e.result = NULL;
	e.env = env;
	e.last_status = last_status;
	e.i = 0;
	e.single = 0;
	e.double_q = 0;
	while (e.str[e.i])
	{
		handle_char(&e);
		e.i++;
	}
	if (!e.result)
		return (ft_strdup(""));
	return (e.result);
}

/* ================= EXPAND ARGS ================= */

static void	expand_args(t_command *cmd, t_env *env, int last_status)
{
	int		i;
	char	*new;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new = expand_string(cmd->args[i], env, last_status);
		free(cmd->args[i]);
		cmd->args[i] = new;
		i++;
	}
	if (cmd->args && cmd->args[0])
		cmd->cmd = cmd->args[0];
}

/* ================= EXPAND REDIRS ================= */

static void	expand_redirs(t_command *cmd, t_env *env, int last_status)
{
	t_redir	*r;
	char	*new;

	r = cmd->redirs;
	while (r)
	{
		if (r->type != T_HEREDOC)
		{
			new = expand_string(r->file, env, last_status);
			free(r->file);
			r->file = new;
		}
		r = r->next;
	}
}

/* ================= MAIN EXPANDER ================= */

void	expander(t_command *cmds, t_shell *s)
{
	while (cmds)
	{
		expand_args(cmds, s->env, s->exit_status);
		expand_redirs(cmds, s->env, s->exit_status);
		cmds = cmds->next;
	}
}
