#include "minishell.h"

/* ================= ADD TOKEN ================= */

int	add_token(t_token **head,
	char *value, t_token_type type)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->value = ft_strdup(value);
	if (!new->value)
		return (free(new), 0);
	new->type = type;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return (1);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

/* ================= IS OPERATOR ================= */

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/* ================= IS SPACE ================= */

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

/* ================= HANDLE OPERATOR ================= */

char	*handle_operator(char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		(*i) += 2;
		return (ft_strdup(">>"));
	}
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		(*i) += 2;
		return (ft_strdup("<<"));
	}
	(*i)++;
	return (ft_substr(line, *i - 1, 1));
}