#include "minishell.h"

/* ================= PIPE ================= */
int	handle_pipe(t_token **tok, t_command **current)
{
	if (!(*current)->cmd && !(*current)->redirs)
		return (0);
	(*current)->next = new_command();
	if (!(*current)->next)
		return (0);
	*current = (*current)->next;
	*tok = (*tok)->next;
	if (!*tok || (*tok)->type == T_PIPE)
		return (0);
	return (1);
}

/* ================= HEREDOC HELPERS ================= */
static int	contains_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static char	*remove_quotes(char *s)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			res[j++] = s[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

/* ================= REDIRECTION ================= */
int	handle_redirection(t_token **tok, t_command *cmd)
{
	t_token	*next;
	char	*file;
	int		quoted;

	next = (*tok)->next;
	if (!next || next->type != T_WORD)
		return (0);
	file = next->value;
	quoted = 0;
	if ((*tok)->type == T_HEREDOC
		&& contains_quote(file))
	{
		quoted = 1;
		file = remove_quotes(file);
	}
	if (!add_redirection(cmd,
			(*tok)->type, file, quoted))
		return (0);
	if (quoted)
		free(file);
	*tok = next->next;
	return (1);
}

/* ================= FINAL VALIDATION ================= */
int	final_validation(t_command *current)
{
	if (!current->cmd && !current->redirs)
		return (0);
	return (1);
}