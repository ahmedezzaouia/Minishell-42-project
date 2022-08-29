/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:20:56 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/29 02:53:51 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	handle_directory(char *cmd)
{
	DIR	*directory;

	directory = opendir(cmd);
	if (cmd[0] == '/' && !directory)
	{
		ft_error_sdnrr(cmd, "No such file or directory");
		g_data.exit_status = 1;
	}
	else if (directory && ft_strchr(cmd, '/'))
	{
		closedir(directory);
		ft_error_sdnrr(cmd, "Is a directory");
		g_data.exit_status = 1;
	}
	else if (!directory && ft_strchr(cmd, '/'))
	{
		ft_error_sdnrr(cmd, "Not a directory");
		g_data.exit_status = 1;
	}
	else
	{
		ft_error_sdnrr(cmd, "command not found");
		g_data.exit_status = 127;
	}
}

void	exec_path(t_AST *pipe_strc, char *command)
{
	if (execve(command, pipe_strc->args, g_data.env_list) == -1)
	{
		handle_directory(command);
		exit(g_data.exit_status);
	}
}

void	exec_commad(t_AST *pipe_strc, int size)
{
	char	*cmd_path;
	char	*cmd;

	(void)size;
	if (pipe_strc->size_redirec > 0)
	{
		if (!handle_redirections(pipe_strc))
			exit(g_data.exit_status);
	}
	if (!pipe_strc->size_args)
		exit(1);
	if (pipe_strc->args[0][0] == 47 || pipe_strc->args[0][0] == '.')
	{
		exec_path(pipe_strc, pipe_strc->args[0]);
	}
	else
	{
		cmd = ft_strjoin(ft_strdup("/"), pipe_strc->args[0]);
		cmd_path = get_path(cmd);
		if (!cmd_path)
			cmd_path = cmd;
		exec_path(pipe_strc, cmd_path);
	}
}

void	execution(t_pipes *pipes)
{
	g_data.is_child = 1;
	init_builtins(pipes);
	if (pipes->nbre_pipes == 1)
		exec_simple_cmd(pipes->tab_cmd[0], pipes->nbre_pipes);
	else if (pipes->nbre_pipes > 1)
		exec_pipe_cmd(pipes);
}
