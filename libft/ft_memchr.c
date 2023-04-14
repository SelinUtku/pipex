/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 03:52:33 by sutku             #+#    #+#             */
/*   Updated: 2022/10/18 04:00:06 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	a;
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	a = c;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == a)
			return (ptr + i);
		i++;
	}
	return (0);
}
