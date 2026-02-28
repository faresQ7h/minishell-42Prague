/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:41:31 by farmoham          #+#    #+#             */
/*   Updated: 2026/02/28 15:49:39 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Create a new env node
*/
t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

/* returns the length of the env linked list */
int	env_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

int	valid_identifier(char *key)
{
	int	i;

	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	env_add_from_envp(t_env **env, char *entry)
{
	t_env	*tmp;
	t_env	*node;
	char	*key;
	char	*equal;

	equal = ft_strchr(entry, '=');
	if (!equal)
		return ;
	key = ft_substr(entry, 0, equal - entry);
	if (!key)
		return ;
	node = env_new(key, equal + 1);
	free(key);
	if (!node)
		return ;
	if (!*env)
		return ((void)(*env = node));
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}
