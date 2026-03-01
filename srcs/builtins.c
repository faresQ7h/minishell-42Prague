/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:41:26 by farmoham          #+#    #+#             */
/*   Updated: 2026/03/01 13:54:34 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** cd builtin
*/
static int	builtin_cd(char **args, t_env **env)
{
	char	*path;

	if (!args[1])
		path = env_get(*env, "HOME");
	else
		path = args[1];
	if (!path || chdir(path) != 0)
	{
		write(2, "cd: error\n", 10);
		return (1);
	}
	return (0);
}

/*
** pwd builtin
*/
static int	builtin_pwd(void)
{
	char	cwd[4096];

	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	return (0);
}

/*
** unset builtin
*/
static int	builtin_unset(char **args, t_env **env)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (!valid_identifier(args[i]))
		{
			write(2, "unset: not a valid identifier\n", 31);
			status = 1;
		}
		else
			env_unset(env, args[i]);
		i++;
	}
	return (status);
}

/*
** exit builtin
*/
static int	builtin_exit(char **args)
{
	int	status;

	status = 0;
	if (args[1])
		status = ft_atoi(args[1]);
	return (status);
}

/*
** Execute builtin
*/
int	exec_builtin(t_command *cmd, t_shell *s)
{
	char	**args;

	args = cmd->args;
	if (!args || !args[0])
		return (1);
	if (!ft_strcmp(args[0], "echo"))
		return (builtin_echo(args));
	else if (!ft_strcmp(args[0], "cd"))
		return (builtin_cd(args, &s->env));
	else if (!ft_strcmp(args[0], "pwd"))
		return (builtin_pwd());
	else if (!ft_strcmp(args[0], "env"))
		return (builtin_env(s->env));
	else if (!ft_strcmp(args[0], "export"))
		return (builtin_export(args, &(s->env)));
	else if (!ft_strcmp(args[0], "unset"))
		return (builtin_unset(args, &(s->env)));
	else if (!ft_strcmp(args[0], "exit"))
		return (builtin_exit(args));
	return (1);
}
