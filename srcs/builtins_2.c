/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:41:18 by farmoham          #+#    #+#             */
/*   Updated: 2026/02/28 15:46:20 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Check if command is a builtin
*/
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

/*
** echo builtin
*/
int	builtin_echo(char **argv)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (argv[1] && !ft_strcmp(argv[1], "-n"))
	{
		nl = 0;
		i++;
	}
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}

/*
** env builtin
*/
int	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->value)
		{
			write(1, env->key, ft_strlen(env->key));
			write(1, "=", 1);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}

/*
** export builtin
*/
static void	export_error_set_status(int *status)
{
	write(2, "export: not a valid identifier\n", 32);
	*status = 1;
}

int	builtin_export(char **argv, t_env **env)
{
	int		i;
	char	*eq;
	int		status;

	i = 1;
	status = 0;
	while (argv[i])
	{
		eq = ft_strchr(argv[i], '=');
		if (eq)
		{
			*eq = '\0';
			if (!valid_identifier(argv[i]))
				export_error_set_status(&status);
			else
				env_set(env, argv[i], eq + 1);
			*eq = '=';
		}
		else if (!valid_identifier(argv[i]))
			export_error_set_status(&status);
		i++;
	}
	return (status);
}
