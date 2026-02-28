#include "minishell.h"

/*
** cd builtin
*/
static int	builtin_cd(char **argv, t_env **env)
{
	char	*path;

	if (!argv[1])
		path = env_get(*env, "HOME");
	else
		path = argv[1];
	if (!path || chdir(path) != 0)
	{
		write(2, "cd: error\n", 10);
		return (1);
	}
	return (0);
}

/*
** export builtin
*/
static int	builtin_export(char **argv, t_env **env)
{
	int		i;
	char	*eq;

	i = 1;
	while (argv[i])
	{
		eq = ft_strchr(argv[i], '=');
		if (eq)
		{
			*eq = '\0';
			env_set(env, argv[i], eq + 1);
			*eq = '=';
		}
		i++;
	}
	return (0);
}

/*
** unset builtin
*/
static int	builtin_unset(char **argv, t_env **env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		env_unset(env, argv[i]);
		i++;
	}
	return (0);
}

/*
** exit builtin
*/
static int	builtin_exit(char **argv)
{
	int	status = 0;

	if (argv[1])
		status = ft_atoi(argv[1]);
	return (status);
}

/*
** Execute builtin
*/
int exec_builtin(t_command *cmd, t_shell *s)
{
	char	**argv;

	argv = cmd->args;
	if (!argv || !argv[0])
		return (1);
	if (!ft_strcmp(argv[0], "echo"))
		return (builtin_echo(argv));
	else if (!ft_strcmp(argv[0], "cd"))
		return (builtin_cd(argv, &s->env));
	else if (!ft_strcmp(argv[0], "pwd"))
		return (builtin_pwd());
	else if (!ft_strcmp(argv[0], "env"))
		return (builtin_env(s->env));
	else if (!ft_strcmp(argv[0], "export"))
		return (builtin_export(argv, &s->env));
	else if (!ft_strcmp(argv[0], "unset"))
		return (builtin_unset(argv, &s->env));
	else if (!ft_strcmp(argv[0], "exit"))
		return (builtin_exit(argv));
	return (1);
}