/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uns_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 01:55:29 by sutku             #+#    #+#             */
/*   Updated: 2023/02/08 12:18:18 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_uns(unsigned int n, int fd)
{
	char	c;

	if (n > 9)
	{
		ft_putnbr_uns(n / 10, fd);
		ft_putnbr_uns(n % 10, fd);
	}
	else
	{
		c = n + 48;
		write(fd, &c, 1);
	}
}

unsigned int	ft_uns_decimal(unsigned int n)
{
	unsigned int	len;

	len = 0;
	ft_putnbr_uns(n, 1);
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		n = n / 10;
		len++;
	}
	return (len);
}
