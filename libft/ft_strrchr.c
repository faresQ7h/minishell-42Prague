/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojetimi <sojetimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:41:50 by sojetimi          #+#    #+#             */
/*   Updated: 2025/04/16 11:48:13 by sojetimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*mut;
	int		s_len;

	mut = (char *)s;
	s_len = ft_strlen(s);
	while (mut[s_len] != (char)c)
	{
		if (s_len-- == 0)
			return (0);
	}
	return (mut + s_len);
}
