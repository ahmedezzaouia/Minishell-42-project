/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:55:59 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/24 23:03:41 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int	display_export(t_AST *cmd)
{
	int	i;

	i = 0;
	if (cmd->size_args == 1)
	{
		while (g_data.env_list[i])
		{
			printf("declare -x %s\n", g_data.env_list[i]);
			i++;
		}
		return (0);
	}
	return (1);
}
