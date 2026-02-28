#include "minishell.h"

static int	init_parser(t_token *tokens,
	t_command **head, t_command **current)
{
	if (!tokens || tokens->type == T_PIPE)
		return (0);
	*head = new_command();
	if (!*head)
		return (0);
	*current = *head;
	return (1);
}

static int	process_token(t_token **tokens,
	t_command **current, t_command *head)
{
	if ((*tokens)->type == T_PIPE)
	{
		if (!handle_pipe(tokens, current))
			return (free_commands(head), 0);
	}
	else if ((*tokens)->type == T_REDIR_IN
		|| (*tokens)->type == T_REDIR_OUT
		|| (*tokens)->type == T_APPEND
		|| (*tokens)->type == T_HEREDOC)
	{
		if (!handle_redirection(tokens, *current))
			return (free_commands(head), 0);
	}
	else
	{
		if (!add_argument(*current, (*tokens)->value))
			return (free_commands(head), 0);
		*tokens = (*tokens)->next;
	}
	return (1);
}

int	parser(t_token *tokens, t_command **commands)
{
	t_command	*head;
	t_command	*current;

	if (!init_parser(tokens, &head, &current))
		return (0);
	while (tokens)
	{
		if (!process_token(&tokens, &current, head))
			return (0);
	}
	if (!final_validation(current))
		return (free_commands(head), 0);
	*commands = head;
	return (1);
}