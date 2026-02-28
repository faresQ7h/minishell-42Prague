/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:07:37 by farmoham          #+#    #+#             */
/*   Updated: 2026/02/28 16:08:03 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_executable(char *cmd, char **paths)
{
	char	*tmp;
	char	*full;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

static char	*search_in_paths(char *cmd, char *path_value)
{
	char	**paths;
	char	*result;

	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	result = find_executable(cmd, paths);
	free_args(paths);
	return (result);
}

static char	*direct_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*get_path(char *cmd, t_env *env)
{
	char	*path_value;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (direct_path(cmd));
	path_value = env_get(env, "PATH");
	if (!path_value)
		return (NULL);
	return (search_in_paths(cmd, path_value));
}
