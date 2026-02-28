/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojetimi <sojetimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:42:44 by sojetimi          #+#    #+#             */
/*   Updated: 2025/04/16 11:48:19 by sojetimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	str_len;

	str_len = ft_strlen(s);
	if (!s)
		return ((void *)0);
	if (start > str_len)
	{
		dst = malloc(1 * sizeof(char));
		if (!dst)
			return ((void *)0);
		dst[0] = '\0';
		return (dst);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return ((void *)0);
	ft_strlcpy(dst, &s[start], len + 1);
	return (dst);
}
