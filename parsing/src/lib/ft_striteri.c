/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:50:52 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/19 22:40:43 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{	
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (*(s + i))
	{
		f(i, (s + i));
		i++;
	}
}
