/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_multiple_commands.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 10:19:14 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/28 19:54:38 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void    output_to_pipe(t_pipes *pipes, int fd[2], int i)
{
    if (i != pipes->nbre_pipes - 1)
    {
        dup2(fd[1], 1);
        close(fd[1]);
    }
    else 
        close(fd[1]);
}

void    read_pipe(int *last_fd)
{
    if (*last_fd != -1)
    {
        dup2(*last_fd, 0);
        close(*last_fd);
    }
}

// void    ft_print_error()
// {
//     printf("Error: \n");
//     exit(1);
// }

void    save_last_pipe(int *last_fd, int fd[2])
{
     if (*last_fd != -1)
        close(*last_fd);
    *last_fd = fd[0];
    close(fd[1]);
}

void    parent_wait_for_childs(int pid, int fd[2])
{
    ft_signal(0);
    while (wait(NULL) != -1)
        wait_child(pid);     
    ft_signal(2);
    close(fd[0]);
    close(fd[1]);
}

void    child_behavior(t_pipes *pipes,int fd[2], int *last_fd, int i)
{
    ft_signal(1);
    output_to_pipe(pipes, fd, i);
    read_pipe(last_fd);
    close(fd[0]);
    exec_simple_cmd(pipes->tab_cmd[i], pipes->nbre_pipes);
}

void    exec_pipe_cmd(t_pipes *pipes)
{
    int i;
    int fd[2];
    int pid;
    int last_fd;

    i = -1;
    last_fd = -1;
    while (++i < pipes->nbre_pipes)
    {
        if (pipe(fd) == -1)
            pipe_err();
        pid = fork();
        if (pid == -1)
        {
            printf("minishell: fork: Resource temporarily unavailable\n");
            break ;
        }
        if (pid == 0)
            child_behavior(pipes, fd, &last_fd, i);
        else
            save_last_pipe(&last_fd, fd);
    }
    parent_wait_for_childs(pid, fd);
}