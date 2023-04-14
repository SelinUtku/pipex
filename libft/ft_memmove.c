/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:42:20 by sutku             #+#    #+#             */
/*   Updated: 2022/10/26 01:05:15 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*n_dst;
	char			*n_src;
	size_t			i;

	n_dst = (char *)dst;
	n_src = (char *)src;
	i = 0;
	if (!n_dst && !n_src)
		return (NULL);
	if (n_dst < n_src)
	{
		while (i < len)
		{
			n_dst[i] = n_src[i];
			i++;
		}
		return (dst);
	}
	while (len > 0)
	{
		n_dst[len - 1] = n_src[len - 1];
		len--;
	}
	return (dst);
}
