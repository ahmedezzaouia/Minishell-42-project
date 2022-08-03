/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:30:45 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/13 15:23:37 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_trim_size(const char *s1, const char *set)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s1) - 1;
	if (len == 0)
		return (len);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[i] && len >= 0 && ft_strchr(set, s1[len]))
	{
		len--;
		i++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		count;
	int		len;
	char	*copy;

	if (!s1)
		return (NULL);
	i = 0;
	count = 0;
	len = ft_strlen(s1);
	count = count_trim_size(s1, set);
	len = len - count;
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = 0;
	while (j < len)
		copy[j++] = s1[i++];
	copy[j] = '\0';
	return (copy);
}
