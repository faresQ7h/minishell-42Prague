#include "minishell.h"

/*
** Initialize env list from envp
*/
t_env	*env_init(char **envp)
{
	t_env	*env;
	t_env	*node;
	t_env	*tmp;
	char	*key;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			key = ft_substr(envp[i], 0,
					ft_strchr(envp[i], '=') - envp[i]);
			node = env_new(key,
					ft_strchr(envp[i], '=') + 1);
			free(key);
			if (!env)
				env = node;
			else
			{
				tmp = env;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = node;
			}
		}
		i++;
	}
	return (env);
}

/*
** Get environment variable value
*/
char	*env_get(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/*
** Set or update environment variable
*/
void	env_set(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = env_new(key, value);
	tmp->next = *env;
	*env = tmp;
}

/*
** Remove environment variable
*/
void	env_unset(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

/* converts the linked list into array */
char	**env_to_array(t_env *env)
{
	char	**arr;
	int		i;
	int		size;
	char	*tmp;

	size = env_size(env);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		arr[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}