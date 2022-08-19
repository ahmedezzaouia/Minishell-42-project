/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:44:29 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/19 17:33:20 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_of_n(int n)
{
	int		i;
	long	num;

	i = 1;
	num = n;
	if (n < 0)
	{
		num = n * (-1);
		i = i + 1;
	}
	while (num / 10)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

static void	filling_str(char *s, int len, long num, int i)
{
	while (len != i)
	{
		s[len - 1] = (num % 10) + '0';
		num = num / 10;
		len --;
	}
}

char	*ft_itoa(int n)
{
	int				len;
	char			*s;
	int				last;
	int				i;
	long			num;

	i = 0;
	len = (int)size_of_n(n);
	last = len - 1;
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	num = n;
	if (n < 0)
	{
		s[i] = '-';
		num = num * (-1);
		i = i + 1;
	}
	filling_str(s, len, num, i);
	s[last + 1] = '\0';
	return (s);
}
