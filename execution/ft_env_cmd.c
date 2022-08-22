/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:00:30 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/22 20:47:09 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	ft_env_cmd(void)
{
	int	i;

	i = 0;
	while (g_data.env_list[i])
	{
		if (ft_strchr(g_data.env_list[i], '='))
		{
			ft_putstr_fd(g_data.env_list[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
}
