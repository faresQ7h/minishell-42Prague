/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojetimi <sojetimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:33:24 by sojetimi          #+#    #+#             */
/*   Updated: 2025/04/16 11:47:54 by sojetimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*dst;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dst = malloc(((s1_len + s2_len + 1) * sizeof(char)));
	if (!dst)
		return ((void *)0);
	ft_strlcpy((dst + ft_strlcpy(dst, s1, s1_len + 1)), s2, s2_len + 1);
	return (dst);
}
