/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 05:35:41 by sutku             #+#    #+#             */
/*   Updated: 2023/02/08 12:18:53 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	itosize_a(int n)
{
	int	size;

	size = 0;
	if (n < 0 && n > -2147483648)
	{
		size++;
		n = -n;
	}
	else if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (11);
	while (n >= 1)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char				*arr;
	int					i;
	int					size;
	long int			temp;

	temp = n;
	size = itosize_a(n);
	i = 1;
	arr = malloc ((size + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	if (temp < 0)
	{
		arr[0] = '-';
		temp = -temp;
	}
	if (temp == 0)
		arr[0] = '0';
	while (temp >= 1)
	{
		arr[size - i++] = (temp % 10) + 48;
		temp /= 10;
	}
	arr[size] = '\0';
	return (arr);
}
