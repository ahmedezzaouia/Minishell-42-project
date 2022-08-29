/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 04:01:25 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/29 13:47:10 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	ft_error_sdnrr(char *cmd, char *msg);

int	redc_input(t_redir **redirec, int *fd, int i)
{
	*fd = open(redirec[i]->filename, O_RDONLY);
	if (*fd == -1)
	{
		if (access(redirec[i]->filename, F_OK) != 0)
		{
			ft_error_sdnrr(redirec[i]->filename, "No such file or directory");
			g_data.exit_status = 1;
		}
		else if (access(redirec[i]->filename, R_OK) != 0)
		{
			ft_error_sdnrr(redirec[i]->filename, "Permission denied");
			g_data.exit_status = 1;
		}
		return (0);
	}
	dup2(*fd, 0);
	close(*fd);
	return (1);
}

int	redc_output(t_redir **redirec, int *fd, int i)
{
	*fd = open(redirec[i]->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd == -1)
	{
		if (access(redirec[i]->filename, W_OK) != 0)
		{
			ft_error_sdnrr(redirec[i]->filename, "Permission denied");
			g_data.exit_status = 1;
		}
		else
			handle_directory(redirec[i]->filename);
		return (0);
	}
	dup2(*fd, 1);
	close(*fd);
	return (1);
}

int	redc_append(t_redir **redirec, int *fd, int i)
{
	*fd = open(redirec[i]->filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (*fd == -1)
	{
		if (access(redirec[i]->filename, W_OK) != 0)
		{
			ft_error_sdnrr(redirec[i]->filename, "Permission denied");
			g_data.exit_status = 1;
		}
		else
			handle_directory(redirec[i]->filename);
		return (0);
	}
	dup2(*fd, 1);
	close(*fd);
	return (1);
}

int	check_redirection(t_redir **redirec, int *fd, int i)
{
	if (redirec[i]->type == INPUT)
	{
		if (!redc_input(redirec, fd, i))
			return (0);
	}
	else if (redirec[i]->type == OUTPUT)
	{
		if (!redc_output(redirec, fd, i))
			return (0);
	}
	else if (redirec[i]->type == APPAND)
	{
		if (!redc_append(redirec, fd, i))
			return (0);
	}
	else if (redirec[i]->type == HERE_DOC)
	{
		dup2(redirec[i]->heredoc[0], 0);
		close(redirec[i]->heredoc[0]);
	}
	return (1);
}

int	handle_redirections(t_AST *pipe_strc)
{
	int			i;
	int			fd;
	t_redir		**redirec;

	i = 0;
	redirec = pipe_strc->redirec;
	if (!redirec)
		return (0);
	while (i < pipe_strc->size_redirec)
	{
		if (!check_redirection(redirec, &fd, i))
			return (0);
		i++;
	}
	return (1);
}
