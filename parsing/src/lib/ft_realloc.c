/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:57:18 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/11 11:40:05 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* adding more memory size to already allocated memory blocks .
The purpose of realloc in C is to expand current memory blocks
while leaving the original content as it is. */

void	*ft_realloc(void *old_alloc, size_t new_size)
{
	unsigned char	*new_alloc;
	size_t			i;

	i = 0;
	if (old_alloc == NULL)
		return (malloc(new_size));
	new_alloc = (unsigned char *)malloc(new_size);
	if (new_alloc == NULL)
		return (NULL);
	ft_memcpy(new_alloc, old_alloc, new_size);
	free(old_alloc);
	return (new_alloc);
}
