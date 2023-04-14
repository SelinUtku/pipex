/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 03:18:24 by sutku             #+#    #+#             */
/*   Updated: 2022/10/30 05:51:18 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printpointer(unsigned long long int n, char *base,
	int fd, int flag)
{
	if (flag == 0)
		write(fd, "0x", 2);
	if (n > 15)
	{
		flag = 1;
		ft_printpointer(n / 16, base, fd, flag);
		ft_printpointer(n % 16, base, fd, flag);
	}
	else
		write(fd, &base[n], 1);
}

unsigned int	ft_pointer(unsigned long long int n)
{
	unsigned int	len;

	len = 0;
	ft_printpointer(n, "0123456789abcdef", 1, 0);
	if (n == 0)
		return (3);
	while (n >= 1)
	{
		n = n / 16;
		len++;
	}
	return (len + 2);
}
