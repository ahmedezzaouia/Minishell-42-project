/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 04:01:25 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/27 13:16:43 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int    handle_redirections(t_AST *pipe_strc)
{
    printf("ahdgadghjagdhjagdhjgajdghjd\n");
    int i;
    int fd;
    t_redir **redirec;

    i = 0;
    redirec = pipe_strc->redirec;
    if (!redirec)
        return (0);
    while (i < pipe_strc->size_redirec)
    {
        if (redirec[i]->type == INPUT)
        {

            fd = open(redirec[i]->filename, O_RDONLY);
            if (fd == -1)
            {
                perror("Minishell: ");
                return (0);
            }

            dup2(fd, 0);
            close(fd);

        }
        else if (redirec[i]->type == OUTPUT)
        {

            fd = open(redirec[i]->filename,  O_CREAT | O_RDWR | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror("Minishell: ");
                return (0);
            }

            dup2(fd, 1);
            close(fd);
  
        }
        else if (redirec[i]->type == APPAND )
        {
            fd = open(redirec[i]->filename,  O_CREAT | O_RDWR | O_APPEND, 0644);
            if (fd == -1)
            {   
                perror("Minishell: ");
                return (0);
            }
            dup2(fd, 1);
            close(fd);
        }
        else if (redirec[i]->type == HERE_DOC)
        {
            dup2(redirec[i]->heredoc[0], 0);
            close(redirec[i]->heredoc[0]);
        }
        i++;
    }
    return (1);
}
