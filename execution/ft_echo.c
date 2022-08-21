/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:38:59 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/21 22:21:03 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int	remove_newline(char *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == 'n')
			i++;
		else
			break ;
	}
	if (s[i] == '\0')
		return (1);
	return (0);
}

void	ft_echo(char **av)
{
	int	i;
	int	rm_newline;
	int	status;

	i = 1;
	status = 1;
	while (av[i])
	{
		if (status && remove_newline(av[i]))
		{
			rm_newline = 1;
			i++;
			continue ;
		}
		status = 0;
		ft_putstr_fd(av[i], 1);
		if (av[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!rm_newline)
		ft_putstr_fd("\n", 1);
}
