/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:46:04 by sutku             #+#    #+#             */
/*   Updated: 2022/10/26 01:07:37 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_src;
	size_t	len_dst;

	len_dst = 0;
	if (dst)
		len_dst = (size_t)ft_strlen(dst);
	len_src = (size_t)ft_strlen(src);
	i = 0;
	if (dstsize <= len_dst)
		return (dstsize + len_src);
	while (src[i] != '\0' && i < (dstsize - len_dst - 1))
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_src + len_dst);
}
