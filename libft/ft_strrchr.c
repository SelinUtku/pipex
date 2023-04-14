/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 00:57:16 by sutku             #+#    #+#             */
/*   Updated: 2022/10/19 01:34:39 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	a;
	char			*ptr;
	int				len;

	len = 0;
	a = (char)c;
	ptr = (char *)s;
	while (ptr[len] != '\0')
		len++;
	while (len >= 0)
	{
		if (ptr[len] == a)
			return (ptr + len);
		len--;
	}
	return (0);
}
