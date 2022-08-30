/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_multiple_commands.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 10:19:14 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/30 01:27:59 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	parent_wait_for_childs(int pid, int fd[2])
{
	ft_signal(0);
	while (wait(NULL) != -1)
		wait_child(pid);
	ft_signal(2);
	close(fd[0]);
	close(fd[1]);
}

void	child_behavior(t_pipes *pipes, int fd[2], int *last_fd, int i)
{
	ft_signal(1);
	output_to_pipe(pipes, fd, i);
	read_pipe(last_fd);
	close(fd[0]);
	exec_simple_cmd(pipes->tab_cmd[i], pipes->nbre_pipes);
}

void	exec_pipe_cmd(t_pipes *pipes)
{
	int	i;
	int	fd[2];
	int	pid;
	int	last_fd;

	i = -1;
	last_fd = -1;
	while (++i < pipes->nbre_pipes)
	{
		if (pipe(fd) == -1)
			pipe_err();
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
			break ;
		}
		if (pid == 0)
			child_behavior(pipes, fd, &last_fd, i);
		else
			save_last_pipe(&last_fd, fd);
	}
	parent_wait_for_childs(pid, fd);
}
