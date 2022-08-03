/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:13:41 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/17 13:21:09 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t			res;
	size_t			i;

	res = ft_strlen(src);
	i = 0;
	if (dstsize > 0)
	{
		while (i < (dstsize - 1) && i < res && src[i])
		{	
			*(dst + i) = *(src + i);
			i++;
		}
		*(dst + i) = '\0';
	}
	return (res);
}
