/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:24:25 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/25 02:43:02 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	env_variable(char **env)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (env[i] != NULL)
	{
		g_data.env_list = ft_realloc_er(g_data.env_list, sizeof(char *), size);
		size += 1;
		g_data.env_list[size - 1] = ft_strdup_er(env[i]);
		i++;
	}
	g_data.env_list = ft_realloc_er(g_data.env_list, sizeof(char *), size);
	size += 1;
	g_data.env_list[size - 1] = NULL;
	g_data.size_env_list = size;
}
