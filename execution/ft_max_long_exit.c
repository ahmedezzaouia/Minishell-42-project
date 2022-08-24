/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_long_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:27:06 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/23 19:40:37 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	exit_with_one_args(char *str)
{
	unsigned char	i;

	if (!check_first_args_is_nbre(str))
		not_numeric(str);
	else
	{
		i = ft_atoi(str);
		check_max_long(i, str);
		write(2, "exit\n", 6);
		exit(i);
	}
}
