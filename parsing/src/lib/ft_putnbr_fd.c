/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 21:32:19 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/20 15:12:18 by ahmaidi          ###   ########.fr       */
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
	}
	while (num / 10)
	{
		num = num / 10;
		i *= 10;
	}
	return (i);
}

static void	filling_str(int fd, int len, long num)
{
	while (len != 0)
	{
		ft_putchar_fd((num / len) + '0', fd);
		num = num % len;
		len /= 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int				len;
	long			num;

	len = (int)size_of_n(n);
	num = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = num * (-1);
	}
	filling_str(fd, len, num);
}
