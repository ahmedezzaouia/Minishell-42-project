/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:33:37 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/29 12:54:30 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	update_old_pwd(char *pwd)
{
	int		oldpwdindex;
	char	*item;

	oldpwdindex = get_oldpwd_index();
	if (g_data.env_list[oldpwdindex] == NULL)
	{
		g_data.env_list = ft_realloc_er(g_data.env_list, \
			sizeof(char *), g_data.size_env_list + 1);
		g_data.env_list[g_data.size_env_list] = ft_strjoin(ft_strdup("OLD"), \
			pwd);
		g_data.env_list[g_data.size_env_list + 1] = NULL;
	}
	else
	{
		item = g_data.env_list[oldpwdindex];
		g_data.env_list[get_oldpwd_index()] = ft_strjoin(ft_strdup("OLD"), pwd);
		free(item);
	}
}

void	change_dir(t_AST *cmd_strc, char *s, char *str_join, char *pwd)
{
	char	*item;

	item = NULL;
	s = getcwd(NULL, 0);
	if (s == NULL)
	{
		item = g_data.env_list[get_pwd_index()];
		ft_putstr_fd("Minishell : error retrieving ", 2);
		ft_putstr_fd("current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		str_join = ft_strjoin(ft_strdup("/"), cmd_strc->args[1]);
		g_data.env_list[get_pwd_index()] = ft_strjoin(ft_strdup(pwd), str_join);
		free(item);
		free(str_join);
	}
	else
	{
		item = g_data.env_list[get_pwd_index()];
		g_data.env_list[get_pwd_index()] = ft_strjoin(ft_strdup("PWD="), s);
		free(item);
	}
	free(s);
}

void	ft_cd_cmd(t_AST *cmd_strc)
{
	char	*str_join;
	char	*pwd;
	char	*s;
	char	*item;

	s = NULL;
	item = NULL;
	str_join = NULL;
	pwd = g_data.env_list[get_pwd_index()];
	update_old_pwd(pwd);
	if (cmd_strc->size_args == 1)
		go_to_home(s);
	else
	{
		if (chdir(cmd_strc->args[1]) == -1)
		{
			ft_error_sdnrr(cmd_strc->args[1], "Not a directory");
			g_data.exit_status = 1;
		}
		else
			change_dir(cmd_strc, s, str_join, pwd);
	}
	free (s);
}
