/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojetimi <sojetimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:26:33 by sojetimi          #+#    #+#             */
/*   Updated: 2025/04/16 11:46:50 by sojetimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *str, char c)
{
	int		i;
	size_t	wcount;

	i = 0;
	wcount = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || !str[i + 1]))
			wcount++;
		i++;
	}
	return (wcount);
}

static void	*error_free(size_t current_word, char **splitted)
{
	while (current_word > 0)
	{
		current_word--;
		free(splitted[current_word]);
	}
	free(splitted);
	return ((void *)0);
}

static size_t	get_word_len(char const *s, size_t i, char c)
{
	size_t	j;

	j = 0;
	while (s[i + j] && s[i + j] != c)
		j++;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char			**splitted;
	size_t			current_word;
	size_t			i;
	size_t			j;

	i = 0;
	current_word = 0;
	splitted = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!splitted)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			j = get_word_len(s, i, c);
			splitted[current_word] = ft_substr(s, i, j);
			if (!splitted[current_word++])
				return (error_free(current_word - 1, splitted));
			i += j;
		}
		else
			i++;
	}
	splitted[current_word] = 0;
	return (splitted);
}
