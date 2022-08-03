/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:20:42 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/19 22:32:38 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	i = (int)len - 1;
	if ((char *)dst > (char *)src)
	{	
		while (i >= 0)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i--;
		}
	}
	else if ((char *)dst < (char *)src)
	{
		i = 0;
		while (i < (int)len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dst);
}
