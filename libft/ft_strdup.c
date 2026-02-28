/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojetimi <sojetimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:30:24 by sojetimi          #+#    #+#             */
/*   Updated: 2025/04/16 11:46:58 by sojetimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	str_len;
	char	*ptr;

	str_len = ft_strlen(s);
	ptr = malloc((str_len * sizeof(char)) + 1);
	if (!ptr)
		return (ptr);
	ptr[str_len] = '\0';
	while (str_len-- > 0)
		ptr[str_len] = s[str_len];
	return (ptr);
}
