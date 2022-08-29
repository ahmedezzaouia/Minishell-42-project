/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:16:50 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/29 12:32:31 by ahmez-za         ###   ########.fr       */
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

int	check_first_args_is_nbre(char *str)
{
	int	i;

	i = 0;
	str = ft_del_fespace(str);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	not_numeric(char *str)
{
	write(1, "exit\n", 6);
	write(2, "Minishell : exit: ", 19);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
	exit(255);
}

void	check_max_long(unsigned char i, char *str)
{
	if (i == 255)
	{
		if (!ft_strncmp(str, "922337203685477580",
				ft_strlen("922337203685477580")))
			if (str[18] - '0' > 7)
				not_numeric(str);
	}
	else if (i == 0)
	{
		if (!ft_strncmp(str, "-922337203685477580",
				ft_strlen("-922337203685477580")))
			if (str[19] - '0' > 8)
				not_numeric(str);
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
		if (!check_first_args_is_nbre(av[1]))
			not_numeric(av[1]);
		write(1, "exit\n", 6);
		write(2, "Minishell : exit: too arguments\n", 33);
		g_data.exit_status = 1;
	}
	else
	{
		write(1, "exit\n", 6);
		exit(g_data.exit_status);
	}
}
