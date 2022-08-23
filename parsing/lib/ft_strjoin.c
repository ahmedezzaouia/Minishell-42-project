/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:52:46 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/23 17:45:47 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char			*str_join;
	unsigned int	i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	str_join = (char *)ft_calloc(1, (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str_join)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		str_join[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		str_join[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	free(s1);
	return (str_join);
}
