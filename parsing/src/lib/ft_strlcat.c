/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:16:58 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/19 20:58:03 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	slen;
	unsigned int	dlen;
	unsigned int	i ;

	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	i = 0;
	if (dstsize == 0)
		return (slen);
	if (dstsize <= dlen)
		return (slen + dstsize);
	while (i < (dstsize - dlen - 1) && i < slen)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (slen + dlen);
}
