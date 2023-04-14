/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 22:50:16 by sutku             #+#    #+#             */
/*   Updated: 2023/01/24 18:23:40 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	check_conditions(va_list ag, char a)
{
	unsigned int	ret;

	ret = 0;
	if (a == 'c')
		ret += ft_putchar(va_arg(ag, int), 1);
	else if (a == 's')
		ret += pf_putstr_fd(va_arg(ag, char *), 1);
	else if (a == 'p')
		ret += ft_pointer(va_arg(ag, unsigned long long int));
	else if (a == 'd' || a == 'i')
		ret += ft_decimal(va_arg(ag, int));
	else if (a == 'u')
		ret += ft_uns_decimal(va_arg(ag, unsigned int));
	else if (a == 'x')
		ret += ft_hexadecimal(va_arg(ag, unsigned long int), 'x');
	else if (a == 'X')
		ret += ft_hexadecimal(va_arg(ag, unsigned long int), 'X');
	else if (a == '%')
	{
		write(1, "%", 1);
		ret++;
	}
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	int				i;
	unsigned int	ret;
	va_list			ag;

	i = 0;
	ret = 0;
	va_start(ag, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			ret += check_conditions(ag, format[i]);
		}
		else
			ret += ft_putchar(format[i], 1);
		i++;
	}
	va_end(ag);
	return (ret);
}
