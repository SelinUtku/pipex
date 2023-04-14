/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:46:56 by sutku             #+#    #+#             */
/*   Updated: 2023/01/24 18:24:06 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	pf_putstr_fd(char *s, int fd)
{
	unsigned int	len;

	len = 0;
	if (!s)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (s[len] != '\0')
		len++;
	write(fd, s, len);
	return (len);
}
