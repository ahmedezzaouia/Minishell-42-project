/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 22:48:21 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/29 00:09:45 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	update_env(char *env)
{
	char	*temp;

	if (ft_strchr(env, '+'))
	{
		g_data.env_list[ft_index_env(env)] = ft_strjoin(
				g_data.env_list[ft_index_env(env)],
				ft_strchr(env, '=') + 1);
	}
	else
	{
		if (ft_strchr(env, '='))
		{
			temp = g_data.env_list[ft_index_env(env)];
			g_data.env_list[ft_index_env(env)] = ft_strdup_er(env);
			free(temp);
		}
	}
}

void	ft_export_add(t_AST *cmd, int i)
{
	g_data.env_list[g_data.size_env_list - 1]
		= filling_args_export(cmd->args[i]);
	g_data.env_list = ft_realloc_er(g_data.env_list,
			sizeof(char *), g_data.size_env_list);
	g_data.size_env_list += 1;
	g_data.env_list[g_data.size_env_list - 1] = NULL;
}
