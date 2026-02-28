/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojetimi <sojetimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:41:31 by sojetimi          #+#    #+#             */
/*   Updated: 2025/04/16 11:48:08 by sojetimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	to_find_len;

	to_find_len = ft_strlen(little);
	i = 0;
	if (!little[0])
		return ((char *)big);
	while (big[i] && (i < len))
	{
		j = 0;
		while ((j < to_find_len) && ((i + j) < len))
		{
			if (big[i + j] != little[j])
				break ;
			j++;
		}
		if (j == to_find_len)
			return ((char *)(big + i));
		i++;
	}
	return (0);
}
