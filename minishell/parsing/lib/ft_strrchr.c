/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:13:23 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/20 13:09:50 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = (int)ft_strlen(s) - 1;
	if (c)
	{
		while (i >= 0)
		{
			if (s[i] == (char)c)
				return ((char *)s + i);
			i--;
		}
		return (NULL);
	}
	else
		return ((char *)s + ft_strlen(s));
}
