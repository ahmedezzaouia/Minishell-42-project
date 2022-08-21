/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:20:56 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/21 17:20:43 by ahmez-za         ###   ########.fr       */
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
    int i;
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
        if (redirec[i]->type == INPUT)
        {

            fd = open(redirec[i]->filename, O_RDONLY);
            if (fd == -1)
            {
                perror("Minishell: ");
                exit(1) ;
            }

            dup2(fd, 0);
            close(fd);

        }
        else if (redirec[i]->type == OUTPUT)
        {

            fd = open(redirec[i]->filename,  O_CREAT | O_RDWR | O_TRUNC, 0644);
            if (fd == -1)
                perror("Minishell: ");
            dup2(fd, 1);
            close(fd);
  
        }
        else if (redirec[i]->type == APPAND )
        {
            fd = open(redirec[i]->filename,  O_CREAT | O_RDWR | O_APPEND, 0644);
            if (fd == -1)
                perror("Minishell: ");
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

void run_builtins(t_AST *pipe_strc)
{
    // (void) pipe_strc;
    // TODO: don't forget to lowercase the commmnd args[0] Cat CAt ...
    char *cmd;
    if (!pipe_strc->args)
        return ;
    cmd = pipe_strc->args[0];
    if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
        ft_cd_cmd(pipe_strc);
    else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
        ft_pwd_cmd();
// printf("run builten\n");
}

void    exec_commad(t_AST *pipe_strc, char **env)
{
    char *cmd_path;
    char *cmd;
    handle_redirections(pipe_strc);
    if (!pipe_strc->size_args)
        exit(0);
    if (pipe_strc->args[0][0] == 47)
        cmd = pipe_strc->args[0];
    else
        cmd = ft_strjoin(ft_strdup("/"), pipe_strc->args[0]);
    cmd_path = get_path(env, cmd);
    printf("command start in execve\n");
    if(execve(cmd_path, pipe_strc->args, env) == -1)
        perror("minishell: ");
}

void    exec_simple_cmd(t_AST *pipe_strc, char **env, int nbre_pipes)
{
    if (pipe_strc->is_builten)
    {
        run_builtins(pipe_strc);
        if (nbre_pipes == 1)
            return ;
        else
            exit(0);
    }
    else if (nbre_pipes == 1)
    { 
        if (fork() == 0)
            exec_commad(pipe_strc, env);
        else
            wait(NULL);
    }
    else if (nbre_pipes > 1)
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
            exec_simple_cmd(pipes->tab_cmd[i], env, pipes->nbre_pipes + 1);
            // child process code end  
        }
        else
        {
            if (last_fd != -1)
                close(last_fd);
            last_fd = fd[0];
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

void check_builtins(t_pipes *pipes)
{
    // TODO: don't forget to lowercase the commmnd args[0] Cat CAt ...
    int i;
    char *cmd;

    i = 0;
    while (i < pipes->nbre_pipes)
    {
        if (!pipes->tab_cmd[i]->size_args)
        {
            pipes->tab_cmd[i]->is_builten = 0;
            i++;
            continue;
            return ;
        }
        cmd = pipes->tab_cmd[i]->args[0];
        if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
            pipes->tab_cmd[i]->is_builten = 1;
        else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
            pipes->tab_cmd[i]->is_builten = 1;
        else
            pipes->tab_cmd[i]->is_builten = 0;
        // printf("cmd == [%s] ****is*** %d\n",pipes->tab_cmd[i]->args[0],pipes->tab_cmd[i]->is_builten)
        i++;
    }
}

void    execution(t_pipes *pipes, char **env)
{   
    (void)env;
    check_builtins(pipes);
    		// visitor(pipes);
    if (pipes->nbre_pipes == 1)
        exec_simple_cmd(pipes->tab_cmd[0], env , pipes->nbre_pipes);
    else if (pipes->nbre_pipes > 1)
        exec_pipe_cmd(pipes, env);
    
}

