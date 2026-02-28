/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojetimi <sojetimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:25:30 by sojetimi          #+#    #+#             */
/*   Updated: 2025/04/16 11:46:43 by sojetimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int				c;
	unsigned int	unb;

	if (n < 0)
	{
		write(fd, "-", 1);
		unb = n * -1;
	}
	else
		unb = (unsigned int)n;
	if (unb / 10 > 9)
		ft_putnbr_fd(unb / 10, fd);
	else if (unb / 10 != 0)
	{
		c = unb / 10 + 48;
		write(fd, &c, 1);
	}
	c = unb % 10 + 48;
	write(fd, &c, 1);
}
