/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:08:39 by farmoham          #+#    #+#             */
/*   Updated: 2026/02/28 16:08:57 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_line(char *line, t_shell *shell)
{
	t_token		*tokens;
	t_command	*commands;

	if (!line || is_empty(line))
		return ;
	add_history(line);
	tokens = lexer(line);
	if (!tokens)
	{
		shell->exit_status = 2;
		return (ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2));
	}
	if (!parser(tokens, &commands))
	{
		shell->exit_status = 2;
		return (free_tokens(tokens), ft_putstr_fd("minishell: invalid syntax\n",
				2));
	}
	free_tokens(tokens);
	expander(commands, shell);
	if (!process_heredocs(commands, shell))
		return (free_commands(commands));
	executor(commands, shell);
	free_commands(commands);
}

void	prompt_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		g_sig = 0;
		line = readline("minishell$ ");
		if (g_sig == 130)
			shell->exit_status = 130;
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		process_line(line, shell);
		free(line);
	}
}
