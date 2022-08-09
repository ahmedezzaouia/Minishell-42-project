/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_er.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:56:22 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/09 17:57:43 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/* Check the return of realloc */
void	*ft_realloc_er(void *ptr, size_t size, size_t oldsize)
{
	void	*newptr;

	ptr = ft_realloc(ptr, size * oldsize, size * (oldsize + 1));
	if (!ptr)
		ft_error(errno);
	retrun (newptr);
}