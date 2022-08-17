/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:20:56 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/17 17:12:40 by ahmaidi          ###   ########.fr       */
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

    path_chunks = ft_split(getenv("PATH"), ':');
    i = 0;
    while (path_chunks[i])
    {
        cmd_joined_path = ft_strjoin(path_chunks[i], cmd);
        if (access(cmd_joined_path, F_OK) == 0)
            return (cmd_joined_path);
        // printf("chunk[%d] == %s\n",i, cmd_joined_path);
        i++;
    }
    // todo :: you have to check if all path are not valid 
    return (NULL);
}
  

int    handle_redirections(t_AST *pipe_strc)
{
    int i;
    int fd;
    t_redir **redirec;

    i = 0;
    redirec = pipe_strc->redirec;
    // if (!redirec)
    //     return (0);
    while (i < pipe_strc->size_redirec)
    {
        
        if (redirec[i]->type == INPUT)
        {
            fd = open(redirec[i]->filename, O_RDONLY);
            if (fd == -1)
            {
                printf("file is not exist\n");
                return (0);
            }
            dup2(fd, 0);
            close(fd);
        }
        else if (redirec[i]->type == OUTPUT)
        {
            fd = open(redirec[i]->filename,  O_CREAT | O_WRONLY , 0644);
            dup2(fd, 1);
        }
        i++;
    }
    return (1);
    
}

void    exec_simple_cmd(t_AST *pipe_strc, char **env)
{
    // check if /user/bin/ls path example or Not
    // printf("exec_simple_cmd called\n");
    char *cmd_path;
    // printf("cmd == %s\n", pipe_strc->args[0]);
    if (pipe_strc->redirec)
        handle_redirections(pipe_strc);
    if (!pipe_strc->args)
    {
        // printf("IS NULL \n");
        exit(1);
    }
    cmd_path = get_path(env, ft_strjoin(ft_strdup("/"), pipe_strc->args[0]));

    // i = 3;
    // while (i < 1024)
    //     close(i++);
    if(execve(cmd_path, pipe_strc->args, env) == -1)
    {
        printf("command not execute\n");
    }
}

void    exec_pipe_cmd(t_pipes *pipes, char **env)
{
    int i;
    int fd[2];
    int pid;
    int last_fd = 0;

    pipes->nbre_pipes--;
    i = 0;
    while (i <= pipes->nbre_pipes)
    {

        if (pipe(fd) == -1)
            ft_print_error();
        pid = fork();
        if (pid == 0)
        {
      
            // child process code start
            if (i != 0)
            {
                dup2(last_fd, STDIN_FILENO);
                close(last_fd);
            }
            if (i != pipes->nbre_pipes)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }
            // printf("pipe called\n");
            exec_simple_cmd(pipes->tab_cmd[i], env);
            // child process code end  
        }
        else
        {
            last_fd = fd[0];
            close(fd[1]);
        }
        i++;
        
    }
    close(fd[0]);
    close(fd[1]);
    i = 0;
    while (i++ <= pipes->nbre_pipes)
        wait(NULL);
    
}

void    execution(t_pipes *pipes, char **env)
{

    if (pipes->nbre_pipes == 1)
        exec_simple_cmd(pipes->tab_cmd[0], env);
    else if (pipes->nbre_pipes > 1)
        exec_pipe_cmd(pipes, env);
    // int i = 3;
    // while (i < 1024)
    //     close(i++);
}

