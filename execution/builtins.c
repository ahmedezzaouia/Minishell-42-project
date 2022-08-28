/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:22:36 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/28 21:20:48 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	init_builtins_check(t_pipes *pipes, int i, char *cmd)
{
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		pipes->tab_cmd[i]->is_builten = 1;
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		pipes->tab_cmd[i]->is_builten = 1;
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		pipes->tab_cmd[i]->is_builten = 1;
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		pipes->tab_cmd[i]->is_builten = 1;
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		pipes->tab_cmd[i]->is_builten = 1;
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		pipes->tab_cmd[i]->is_builten = 1;
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		pipes->tab_cmd[i]->is_builten = 1;
	else
		pipes->tab_cmd[i]->is_builten = 0;
}

void	init_builtins(t_pipes *pipes)
{
	int		i;
	char	*cmd;

	i = 0;
	while (i < pipes->nbre_pipes)
	{
		if (!pipes->tab_cmd[i]->size_args)
		{
			pipes->tab_cmd[i]->is_builten = 0;
			i++;
			continue ;
			return ;
		}
		cmd = pipes->tab_cmd[i]->args[0];
		init_builtins_check(pipes, i, cmd);
		i++;
	}
}

void	run_builtins_check(t_AST *pipe_strc, char *cmd)
{
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		ft_cd_cmd(pipe_strc);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		ft_pwd_cmd();
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		ft_echo(pipe_strc->args);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		ft_env_cmd();
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		ft_exit(pipe_strc->args, pipe_strc->size_args);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		ft_unset(pipe_strc);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		ft_export(pipe_strc);
}

void	run_builtins(t_AST *pipe_strc, int size)
{
	int		std_out;
	char	*cmd;

	std_out = -1;
	std_out = dup(1);
	if (pipe_strc->size_redirec > 0)
	{
		if (!handle_redirections(pipe_strc))
		{
			if (size == 1)
				return ;
			else if (size > 1)
				exit(g_data.exit_status);
		}
	}
	if (!pipe_strc->args)
		return ;
	cmd = pipe_strc->args[0];
	run_builtins_check(pipe_strc, cmd);
	close(1);
	dup2(std_out, 1);
}
