/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_multiple_commands_utils.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 00:14:57 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/29 00:18:17 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	output_to_pipe(t_pipes *pipes, int fd[2], int i)
{
	if (i != pipes->nbre_pipes - 1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	else
		close(fd[1]);
}

void	read_pipe(int *last_fd)
{
	if (*last_fd != -1)
	{
		dup2(*last_fd, 0);
		close(*last_fd);
	}
}

void	save_last_pipe(int *last_fd, int fd[2])
{
	if (*last_fd != -1)
		close(*last_fd);
	*last_fd = fd[0];
	close(fd[1]);
}
