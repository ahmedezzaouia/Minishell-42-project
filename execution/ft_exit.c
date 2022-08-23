/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:16:50 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/23 16:31:16 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

static char	*ft_del_fespace(char *str)
{
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\f' || *str == '\v' || *str == '\r'))
	{
		str++;
	}
	return (str);
}

static int	check_first_args_is_nbre(char *str)
{
	int	i;

	i = 0;
	str = ft_del_fespace(str);
	if (str[i] == '-' || str[i] == '+')
		i++;
	return (ft_isdigit(str[i]));
}

static void	exit_with_one_args(char *str)
{
	unsigned char	i;

	if (!check_first_args_is_nbre(str))
	{
		write(2, "exit\n", 6);
		write(2, "Minishell : exit: ", 19);
		write(2, str, ft_strlen(str));
		write(2, " numeric argument required\n", 28);
		exit(255);
	}
	else
	{
		i = ft_atoi(str);
		write(2, "exit\n", 6);
		exit(i);
	}
}

void	ft_exit(char **av, unsigned int size)
{

	if (size == 2)
	{
		exit_with_one_args(av[1]);
	}
	else if (size > 2)
	{
		write(2, "exit\n", 6);
		write(2, "Minishell : exit: too arguments\n", 33);
		exit(1);
	}
	else
	{
		write(2, "exit\n", 6);
		exit(0);
	}
}
