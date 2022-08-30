/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:33:37 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/30 01:38:41 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	create_old_pwd(void)
{
	t_AST	*ast;

	ast = malloc(sizeof(t_AST) * 1);
	ast->args = ft_calloc(sizeof(char *), 3);
	ast->args[0] = ft_strdup("export");
	ast->args[1] = ft_strdup("OLDPWD=");
	ast->size_args = 2;
	ast->size_redirec = 0;
	ast->redirec = NULL;
	ft_export(ast);
	free_ast_cmd(ast);
}

void	update_old_pwd(char *pwd)
{
	int		oldpwdindex;
	char	*item;

	oldpwdindex = get_oldpwd_index();
	if (oldpwdindex == -1)
		create_old_pwd();
	else
	{
		item = g_data.env_list[oldpwdindex];
		if (g_data.pwd)
		{
			g_data.env_list[oldpwdindex \
				] = ft_strjoin(ft_strdup("OLD"), g_data.pwd);
		}
		else
		{
			g_data.env_list[oldpwdindex] = ft_strjoin(ft_strdup("OLD"), pwd);
		}
		free(item);
	}
}

void	change_dir_normal(char *s)
{
	char	*item;

	if (g_data.pwd)
	{
		item = g_data.pwd;
		g_data.pwd = ft_strjoin(ft_strdup("PWD="), s);
		free(item);
	}
	else
	{
		item = g_data.env_list[get_pwd_index()];
		g_data.env_list[get_pwd_index()] = ft_strjoin(ft_strdup("PWD="), s);
		free (item);
	}
}

void	change_dir(t_AST *cmd_strc, char *s, char *str_join)
{
	s = getcwd(NULL, 0);
	if (s == NULL)
	{
		ft_putstr_fd("Minishell : error retrieving ", 2);
		ft_putstr_fd("current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		str_join = ft_strjoin(ft_strdup("/"), cmd_strc->args[1]);
		if (g_data.pwd)
			g_data.pwd = ft_strjoin(g_data.pwd, str_join);
		else
			g_data.env_list[get_pwd_index()] = ft_strjoin(g_data.pwd, str_join);
		free(str_join);
	}
	else
		change_dir_normal(s);
	free(s);
}

void	ft_cd_cmd(t_AST *cmd_strc)
{
	char	*str_join;
	char	*pwd;
	char	*s;

	s = NULL;
	str_join = NULL;
	pwd = g_data.env_list[get_pwd_index()];
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
		{
			update_old_pwd(pwd);
			change_dir(cmd_strc, s, str_join);
		}
	}
	free (s);
}
