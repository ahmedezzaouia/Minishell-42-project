/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_er.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:56:22 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/24 00:42:36 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/* Check the return of realloc */
void	*ft_realloc_er(void *old_alloc, size_t count, size_t old_size)
{
	void	*new_allo;

	new_allo = ft_realloc(old_alloc, count * old_size, count * (old_size + 1));
	if (new_allo == NULL)
		ft_error(errno);
	return (new_allo);
}
