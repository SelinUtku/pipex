/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 06:36:19 by sutku             #+#    #+#             */
/*   Updated: 2022/11/28 21:18:32 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_fd(unsigned int n, int fd, char *base)
{
	if (n > 15)
	{
		ft_putnbr_fd(n / 16, fd, base);
		ft_putnbr_fd(n % 16, fd, base);
	}
	else
		write(fd, &base[n], 1);
}

unsigned int	ft_hexadecimal(unsigned int n, char c)
{
	unsigned int	len;

	len = 0;
	if (c == 'x')
		ft_putnbr_fd(n, 1, "0123456789abcdef");
	else if (c == 'X')
		ft_putnbr_fd(n, 1, "0123456789ABCDEF");
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		n = n / 16;
		len++;
	}
	return (len);
}
