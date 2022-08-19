/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:01:05 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/08 14:42:36 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if ((int)len < 0 || len > ft_strlen(big))
		len = ft_strlen(big);
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (big[i] != '\0' && i < (int)len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < (int)len)
		{
			j++;
			if (little[j] == '\0')
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
