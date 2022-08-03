/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:52:46 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/15 17:04:13 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str_join;
	size_t			s1_len;
	size_t			s2_len;
	unsigned int	i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_join = (char *)ft_calloc(sizeof(char), (s1_len + s2_len + 1));
	if (!str_join)
		return (NULL);
	while (i < s1_len)
	{
		str_join[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		str_join[i + s1_len] = s2[i];
		i++;
	}
	return (str_join);
}
