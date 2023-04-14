/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 02:22:59 by sutku             #+#    #+#             */
/*   Updated: 2022/10/20 07:32:50 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	a;
	char			*ptr;
	int				i;

	i = 0;
	a = c;
	ptr = (char *)s;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == a)
			return (ptr + i);
		i++;
	}
	if (ptr[i] == a)
		return (ptr + i);
	return (0);
}
