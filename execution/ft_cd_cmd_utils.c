/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 00:34:27 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/29 16:58:37 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int	get_pwd_index(void)
{
	int	i;

	i = 0;
	while (g_data.env_list[i] && ft_strncmp(g_data.env_list[i], "PWD=", 4))
		i++;
	return (i);
}

int	get_oldpwd_index(void)
{
	int	i;

	i = 0;
	while (g_data.env_list[i] && ft_strncmp(g_data.env_list[i], "OLDPWD=", 7))
		i++;
	return (i);
}

void	go_to_home(char *s)
{
	char	*item;
	char	*home;

	item = NULL;
	home = ft_get_env("HOME");
	if (chdir(home) == -1)
		perror("Minishell :");
	else
	{
		s = getcwd(NULL, 0);
		item = g_data.env_list[get_pwd_index()];
		g_data.env_list[get_pwd_index()] = ft_strjoin(ft_strdup("PWD="), s);
		free(item);
		free(s);
	}
	free(home);
}
