#include "minishell.h"

/* ================= PROCESS OPERATOR ================= */

static int	process_operator(t_token **head,
	char *line, int *i)
{
	char	*op;

	op = handle_operator(line, i);
	if (!op)
		return (0);
	if (!add_token(head, op, get_type(op)))
		return (free(op), 0);
	free(op);
	return (1);
}

/* ================= PROCESS WORD ================= */

static int	process_word(t_token **head,
	char *line, int *i)
{
	char	*word;

	word = extract_word(line, i);
	if (!word)
		return (0);
	if (!add_token(head, word, T_WORD))
		return (free(word), 0);
	free(word);
	return (1);
}

/* ================= LEXER ================= */

t_token	*lexer(char *line)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (line && line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (is_operator(line[i]))
		{
			if (!process_operator(&head, line, &i))
				return (free_tokens(head), NULL);
		}
		else
		{
			if (!process_word(&head, line, &i))
				return (free_tokens(head), NULL);
		}
	}
	return (head);
}