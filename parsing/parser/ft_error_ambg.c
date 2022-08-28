/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_ambg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:29:05 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/28 18:37:36 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	ft_error_ambg(void)
{
	if (g_data.nb_of_ambg > 0)
	{
		while (g_data.nb_of_ambg > 0)
		{
			write(2, "Minishell: ambiguous redirect\n", 31);
			g_data.nb_of_ambg--;
		}
		g_data.exit_status = 1;
	}
}
