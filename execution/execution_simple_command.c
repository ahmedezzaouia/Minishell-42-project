/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_simple_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 10:03:06 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/28 10:17:12 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void    wait_child(int pid)
{
    if (pid)
    {
        waitpid(pid, &g_data.exit_status, 0);
        if (WIFEXITED(g_data.exit_status))
            g_data.exit_status = WEXITSTATUS(g_data.exit_status);
        else if (g_data.exit_status == 3 || g_data.exit_status == 2)
             g_data.exit_status += 128;
    }
}
void    one_command(t_AST *pipe_strc, int nbre_pipes)
{
    int pid;

    pid = fork();
    if (pid == 0)
    {
        ft_signal(1);
        exec_commad(pipe_strc, nbre_pipes);
    }
    else
    {
        ft_signal(0);
        wait_child(pid);
        ft_signal(2);
    }
}

void    exec_simple_cmd(t_AST *pipe_strc, int nbre_pipes)
{
    if (pipe_strc->is_builten)
    {
        run_builtins(pipe_strc, nbre_pipes);
        if (nbre_pipes == 1)
            return ;
        else
            exit(g_data.exit_status);
    }
    else if (nbre_pipes == 1)
        one_command(pipe_strc, nbre_pipes);
    else if (nbre_pipes > 1)
        exec_commad(pipe_strc, nbre_pipes); 
}
