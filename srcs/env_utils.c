#include "minishell.h"

/*
** Create a new env node
*/
t_env *env_new(char *key, char *value)
{
    t_env *new;

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