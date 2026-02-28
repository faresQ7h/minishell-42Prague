#include "minishell.h"

/* ================= EXPAND $? ================= */

static void	expand_exit_status(t_expand *e)
{
	char	*value;

	value = ft_itoa(e->last_status);
	e->result = append_str(e->result, value);
	e->i++;
}

/* ================= EXPAND ENV VAR ================= */

static void	expand_env_variable(t_expand *e)
{
	char	*name;
	char	*value;
	int		start;

	e->i++;
	start = e->i;
	while (e->str[e->i]
		&& (ft_isalnum(e->str[e->i])
		|| e->str[e->i] == '_'))
		e->i++;
	name = ft_substr(e->str, start, e->i - start);
	e->i--;
	value = env_get(e->env, name);
	if (value)
		e->result = append_str(
			e->result, ft_strdup(value));
	free(name);
}

/* ================= EXPAND VARIABLE ================= */

void	expand_variable(t_expand *e)
{
	if (e->str[e->i + 1] == '?')
	{
		expand_exit_status(e);
		return ;
	}
	if (!ft_isalnum(e->str[e->i + 1])
		&& e->str[e->i + 1] != '_')
	{
		e->result = ft_strjoin_char(
			e->result, '$');
		return ;
	}
	expand_env_variable(e);
}