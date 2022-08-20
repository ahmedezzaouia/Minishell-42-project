/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:20:56 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/20 23:46:59 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void    ft_print_error()
{
    printf("Error: \n");
    exit(1);
}

char    *get_path(char **env, char *cmd)
{
    // printf("get path called\n");
    // check if argement is path already or not 
    int i;
    // char *path;
    (void)env;
    char    **path_chunks;
    char    *cmd_joined_path;

    i = 0;
    // printf("cmd == %s\n", cmd);
    path_chunks = ft_split(getenv("PATH"), ':');
    while (path_chunks[i])
    {
        cmd_joined_path = ft_strjoin(path_chunks[i], cmd);
        if (access(cmd_joined_path, F_OK) == 0)
            return (cmd_joined_path);
        i++;
    }
    // todo :: you have to check if all path are not valid 
    return (cmd);
}
  
// int    search_for_next_redirec_type(t_AST *pipe_strc, t_type_redir type, int red_index)
// {
//     while (red_index < pipe_strc->size_redirec)
//     {
//         if (pipe_strc->redirec[red_index]->type == type)
//             return (1);
//         red_index++;
//     }
//     return (0);
// }

int    handle_redirections(t_AST *pipe_strc)
{
    int i;
    int fd;
    t_redir **redirec;

    i = 0;
    redirec = pipe_strc->redirec;
    if (!redirec)
        return (0);
    while (i < pipe_strc->size_redirec)
    {
        // printf("type == %d **** filename == %s\n", redirec[i]->type, redirec[i]->filename);
        
        if (redirec[i]->type == INPUT)
        {

            fd = open(redirec[i]->filename, O_RDONLY);
            if (fd == -1)
                perror("Minishell\n");

            dup2(fd, 0);
            close(fd);

        }
        else if (redirec[i]->type == OUTPUT)
        {

            fd = open(redirec[i]->filename,  O_CREAT | O_RDWR | O_TRUNC, 0644);
            if (fd == -1)
                perror("Minishell\n");
            dup2(fd, 1);
            close(fd);
  
        }
        else if (redirec[i]->type == APPAND )
        {
            fd = open(redirec[i]->filename,  O_CREAT | O_RDWR | O_APPEND, 0644);
            if (fd == -1)
                perror("Minishell\n");
            dup2(fd, 1);
            close(fd);
        }
        else if (redirec[i]->type == HERE_DOC)
        {
            // char *str;
            
            // str = NULL;
            // if (search_for_next_redirec_type(pipe_strc, HERE_DOC, i + 1))
            //     is_last_herdoc = 1;
            // else
            // {
            //     if (pipe(p) == -1)
            //         ft_print_error();
            //     is_last_herdoc = 0;
            // }
            // while ((str = get_next_line(0)))
            // {   
            //     if (!ft_strncmp(str, redirec[i]->filename, ft_strlen(redirec[i]->filename)))
            //     {
            //         free(str);
            //         break ;
            //     }
            //     ft_putstr_fd(str, p[1]);
            //     free(str);
            // }
            // if (!is_last_herdoc)
            // {
            //     dup2(p[0], 0);
            //     handle_redirections(pipe_strc, 2);
            // }

            // close(p[0]);
            // close(p[1]);
            // if (!is_last_herdoc)
            //     break ;

            dup2(redirec[i]->heredoc[0], 0);
            close(redirec[i]->heredoc[0]);
        }
        i++;
    }
    return (1);
    
}

void    exec_commad(t_AST *pipe_strc, char **env)
{
    char *cmd_path;
    char *cmd;

    handle_redirections(pipe_strc);

    // if (!pipe_strc->args)
    // {
    //     exit(1);
    // }

    if (pipe_strc->args[0][0] == 47)
        cmd = pipe_strc->args[0];
    else
        cmd = ft_strjoin(ft_strdup("/"), pipe_strc->args[0]);

    cmd_path = get_path(env, cmd);
    printf("cmd_path === %s\n\n", cmd_path);
    // printf("cmd_path == %s\n",cmd_path);
    if(execve(cmd_path, pipe_strc->args, env) == -1)
    {
        perror("minishell: ");

    }
}

void    exec_simple_cmd(t_AST *pipe_strc, char **env, int nbre_pipes)
{
    // (void)nbre_pipes;
    if (nbre_pipes == 1)
    { 
        if (fork() == 0)
            exec_commad(pipe_strc, env);
        else
            wait(NULL);
    }
    else
        exec_commad(pipe_strc, env);
    
    
}

void    exec_pipe_cmd(t_pipes *pipes, char **env)
{
    int i;
    int fd[2];
    int pid;
    int last_fd = -1;

    pipes->nbre_pipes--;
    i = 0;
    while (i <= pipes->nbre_pipes)
    {
        if (pipe(fd) == -1)
            ft_print_error();
        // printf("====>%s\n", pipes->tab_cmd[i]->args[0]);
        pid = fork();
        if (pid == -1)
        {
            printf("minishell: fork: Resource temporarily unavailable\n");
            break ;
        }
        if (pid == 0)
        {
      
            // child process code start
            if (i != pipes->nbre_pipes)
            {
                dup2(fd[1], 1);
                close(fd[1]);
            }
            else 
                close(fd[1]);
            if (last_fd != -1)
            {
                dup2(last_fd, 0);
                close(last_fd);
            }
            close(fd[0]);
            // printf("pipe called\n");
            exec_simple_cmd(pipes->tab_cmd[i], env, pipes->nbre_pipes + 1);
            // child process code end  
        }
        else
        {
            if (last_fd != -1)
                close(last_fd);
            last_fd = fd[0];
            // printf("cmd == %s **** last_fd ===== %d in [i] == %d with pip[%d -- %d]\n", pipes->tab_cmd[i]->args[0], i, fd[0], fd[1]);
            close(fd[1]);
        }
        i++;
    }
    i = 0;
    int res = 0;
    while (res != -1) 
        res = waitpid(-1, NULL, 0);    
    close(fd[0]);
    close(fd[1]);
}

void    execution(t_pipes *pipes, char **env)
{

    if (pipes->nbre_pipes == 1)
        exec_simple_cmd(pipes->tab_cmd[0], env , pipes->nbre_pipes);
    else if (pipes->nbre_pipes > 1)
        exec_pipe_cmd(pipes, env);
    // int i = 3;
    // while (i < 1024)
    //     close(i++);
}

