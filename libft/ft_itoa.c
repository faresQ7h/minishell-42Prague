/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojetimi <sojetimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:59:49 by sojetimi          #+#    #+#             */
/*   Updated: 2025/04/16 11:44:34 by sojetimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_digits(unsigned int n)
{
	size_t	digits;

	digits = 1;
	while (n / 10 > 0)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char			*n_str;
	unsigned int	unb;
	size_t			i;
	size_t			digits;

	if (n < 0)
		unb = n * -1;
	else
		unb = (unsigned int)n;
	digits = get_digits(unb);
	n_str = malloc((digits + (n < 0) + 1) * sizeof(char));
	if (!n_str)
		return ((void *)0);
	if ((n < 0))
		n_str[0] = '-';
	i = digits;
	while (i > 0)
	{
		n_str[i-- + (n < 0) - 1] = (unb % 10) + 48;
		unb /= 10;
	}
	n_str[digits + (n < 0)] = '\0';
	return (n_str);
}
