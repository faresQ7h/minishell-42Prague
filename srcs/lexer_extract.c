#include "minishell.h"


/* ================= EXTRACT QUOTED PART ================= */

static char	*extract_quoted_part(char *line, int *i)
{
	char	quote;
	int		start;

	quote = line[*i];
	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
		return (NULL);
	(*i)++;
	return (ft_substr(line, start, *i - start));
}

/* ================= EXTRACT PLAIN PART ================= */

static char	*extract_plain_part(char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i]
		&& !is_space(line[*i])
		&& !is_operator(line[*i])
		&& line[*i] != '\''
		&& line[*i] != '"')
		(*i)++;
	return (ft_substr(line, start, *i - start));
}

/* ================= EXTRACT WORD ================= */

char	*extract_word(char *line, int *i)
{
	char	*word;
	char	*part;
	char	*tmp;

	word = NULL;
	while (line[*i]
		&& !is_space(line[*i])
		&& !is_operator(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
			part = extract_quoted_part(line, i);
		else
			part = extract_plain_part(line, i);
		if (!part)
			return (free(word), NULL);
		tmp = append_str(word, part);
		if (!tmp)
			return (free(word), NULL);
		word = tmp;
	}
	return (word);
}

/* ================= GET TYPE ================= */

t_token_type	get_type(char *s)
{
	if (!ft_strcmp(s, "|"))
		return (T_PIPE);
	if (!ft_strcmp(s, "<"))
		return (T_REDIR_IN);
	if (!ft_strcmp(s, ">"))
		return (T_REDIR_OUT);
	if (!ft_strcmp(s, ">>"))
		return (T_APPEND);
	if (!ft_strcmp(s, "<<"))
		return (T_HEREDOC);
	return (T_WORD);
}