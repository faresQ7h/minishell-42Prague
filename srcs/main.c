/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:06:29 by farmoham          #+#    #+#             */
/*   Updated: 2026/03/01 00:46:29 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env = env_init(envp);
	shell.exit_status = 0;
	shell.last_pid = -1;
	shell.cmds_head = NULL;
	init_signals_interactive();
	prompt_loop(&shell);
	free_env(shell.env);
	rl_clear_history();
	return (shell.exit_status);
}
