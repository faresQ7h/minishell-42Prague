#include "minishell.h"

/*
** Returns 1 if the string contains only spaces or tabs
** Used to ignore empty commands like:
**   - ""
**   - "   "
**   - "\t\t"
*/
int	is_empty(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

/*
** Frees a NULL-terminated array of strings
** Used after lexer() and execution
*/
char	*ft_strjoin_char(char *s, char c)
{
	char	*res;
	size_t	i;

	if (!s)
	{
		res = malloc(2);
		if (!res)
			return (NULL);
		res[0] = c;
		res[1] = '\0';
		return (res);
	}
	res = malloc(ft_strlen(s) + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	free(s);
	return (res);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*append_str(char *s1, char *s2)
{
	char	*res;

	if (!s1)
	{
		res = ft_strdup(s2);
		free(s2);
		return (res);
	}
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}
