/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 00:50:36 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/29 15:55:56 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int	is_exist_on_env_list(char *arg)
{
	int		i;
	char	*str;
	char	*str2;

	i = 0;
	str = ft_strdup_er(arg);
	str2 = ft_strdup_er(arg);
	str = ft_strjoin(str, "=");
	while (g_data.env_list[i])
	{
		if (!ft_strncmp(g_data.env_list[i], str, ft_strlen(str)) || \
			!ft_strncmp(g_data.env_list[i], str2, ft_strlen(str2) + 1))
		{
			free (str);
			free (str2);
			return (i);
		}
		i++;
	}
	free(str);
	free(str2);
	return (-1);
}

void	fill_new_env_list(int i, int j, int remove_index, char **new_env_list)
{
	while (g_data.env_list[i])
	{
		if (i == remove_index)
		{
			free (g_data.env_list[i]);
			i++;
			continue ;
		}
		new_env_list[j] = ft_strdup(g_data.env_list[i]);
		free (g_data.env_list[i]);
		i++;
		j++;
	}
}

void	delete_env(char *arg)
{
	int		i;
	int		j;
	char	**new_env_list;
	int		remove_index;

	i = 0;
	j = 0;
	remove_index = is_exist_on_env_list(arg);
	if (remove_index == -1)
		return ;
	g_data.size_env_list -= 1;
	new_env_list = ft_calloc(sizeof(char *), g_data.size_env_list);
	if (!new_env_list)
		return ;
	fill_new_env_list(i, j, remove_index, new_env_list);
	free (g_data.env_list);
	g_data.env_list = new_env_list;
}
