#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env = env_init(envp);
	shell.exit_status = 0;
	shell.last_pid = -1;
	init_signals_interactive();
	prompt_loop(&shell);
	free_env(shell.env);
	return (shell.exit_status);
}
