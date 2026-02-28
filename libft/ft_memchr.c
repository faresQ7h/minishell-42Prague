/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojetimi <sojetimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:06:23 by sojetimi          #+#    #+#             */
/*   Updated: 2025/04/16 11:44:59 by sojetimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*mut;

	mut = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*mut == (unsigned char)c)
			return (mut);
		mut++;
	}
	return (0);
}
