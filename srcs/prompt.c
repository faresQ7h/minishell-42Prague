#include "minishell.h"
/*======================= FOR TESTING LEXER + PARSER + EXPANDER ======================*/
// static void	process_line(char *line, t_shell *shell)
// {
// 	t_token		*tokens;
// 	t_command	*commands;

// 	commands = NULL;
// 	tokens = NULL;

// 	if (!line || is_empty(line))
// 		return ;

// 	add_history(line);

// 	tokens = lexer(line);
// 	if (!tokens)
// 	{
// 		shell->exit_status = 2;
// 		ft_putstr_fd(
// 			"minishell: syntax error: unclosed quote\n", 2);
// 		return ;
// 	}

// 	print_tokens(tokens);

// 	if (!parser(tokens, &commands) || !commands)
// 	{
// 		shell->exit_status = 2;
// 		free_tokens(tokens);
// 		ft_putstr_fd(
// 			"minishell: invalid syntax\n", 2);
// 		return ;
// 	}

// 	print_commands(commands);

// 	free_tokens(tokens);

// 	expander(commands,
// 		shell->env,
// 		shell->exit_status);

// 	printf("---- AFTER EXPANDER ----\n");
// 	print_commands(commands);

// 	free_commands(commands);
// }
/*===============================================================*/


static void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_command *commands;

	if (!line || is_empty(line))
		return ;
	add_history(line);
	tokens = lexer(line);
	if (!tokens) //return NULL if unclosed qoutes is detected
	{
		shell->exit_status = 2;
		return (ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2));
	}
	if (!parser(tokens, &commands))
	{
		shell->exit_status = 2;
		return (free_tokens(tokens),
			ft_putstr_fd("minishell: invalid syntax\n", 2));
	}
	free_tokens(tokens);
	expander(commands, shell);
	if (!process_heredocs(commands, shell)) // handell all the hereodc before we fork and creat new childs
		return (free_commands(commands));
	executor(commands, shell);
	free_commands(commands);
}

void	prompt_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		process_line(line, shell);
		free(line);
	}
}
