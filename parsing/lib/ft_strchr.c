/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:08:45 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/19 18:03:55 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if ((char)c)
	{
		while (s[i] != '\0')
		{
			if (s[i] == (char)c)
				return ((char *)s + i);
			i++;
		}
		return (NULL);
	}
	else
		return ((char *)s + ft_strlen(s));
}
