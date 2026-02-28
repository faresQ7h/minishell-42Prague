/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:06:29 by farmoham          #+#    #+#             */
/*   Updated: 2026/02/28 16:06:44 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(int ac, char **av, char **envp)
{
	t_shell		shell;

	(void)ac;
	(void)av;
	shell.env = env_init(envp);
	shell.exit_status = 0;
	shell.last_pid = -1;
	shell.cmds_head = NULL;
	disable_echoctl();
	init_signals_interactive();
	prompt_loop(&shell);
	free_env(shell.env);
	rl_clear_history();
	return (shell.exit_status);
}
