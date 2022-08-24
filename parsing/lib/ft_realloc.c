/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:57:18 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/24 03:09:26 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* adding more memory size to already allocated memory blocks .
The purpose of realloc in C is to expand current memory blocks
while leaving the original content as it is. */

void	*ft_realloc(void *old_alloc, size_t old_size, size_t new_size)
{
	unsigned char	*old_alloc_t;
	unsigned char	*new_alloc;
	size_t			i;

	i = 0;
	if (old_alloc == NULL)
		return (malloc(new_size));
	old_alloc_t = (unsigned char *)old_alloc;
	new_alloc = (unsigned char *)malloc(new_size);
	if (new_alloc == NULL)
		return (NULL);
	while (i < old_size && i < new_size)
	{
		new_alloc[i] = old_alloc_t[i];
		i++;
	}
	free(old_alloc);
	return (new_alloc);
}
