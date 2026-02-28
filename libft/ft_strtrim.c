/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojetimi <sojetimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:42:14 by sojetimi          #+#    #+#             */
/*   Updated: 2025/04/16 11:48:17 by sojetimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_trimable(char c, char const *set)
{
	unsigned int	i;

	i = -1;
	while (set[++i])
	{
		if (set[i] == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	size_t			len;

	start = 0;
	while (s1[start] && is_trimable(s1[start], set))
		start++;
	len = ft_strlen(s1) - start;
	while (len > 0 && is_trimable((s1 + start)[len - 1], set))
		len--;
	return (ft_substr(s1, start, len));
}
