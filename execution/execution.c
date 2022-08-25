/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:20:56 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/25 02:19:02 by ahmez-za         ###   ########.fr       */
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
    int j;
    (void)env;
    char    **path_chunks;
    char    *cmd_joined_path;

    i = 0;
    // printf("cmd == %s\n", cmd);
    path_chunks = ft_split(getenv("PATH"), ':');
    while (path_chunks[i])
    {
        cmd_joined_path = ft_strjoin(ft_strdup(path_chunks[i]), cmd);
        if (access(cmd_joined_path, F_OK) == 0)
        {
            j = -1;
            while (path_chunks[++j])
                free(path_chunks[j]);
            free(path_chunks);
            return (cmd_joined_path);
        }
        free(cmd_joined_path);
        i++;
    }
    i = -1;
    while (path_chunks[++i])
        free(path_chunks[i]);
    free(path_chunks);
    // todo :: you have to check if all path are not valid 
    return (cmd);
}

void run_builtins(t_AST *pipe_strc, int size)
{
    int std_out;
    // (void) pipe_strc;
    // TODO: don't forget to lowercase the commmnd args[0] Cat CAt ...
    char *cmd;
    std_out = -1;
    std_out = dup(1);
    if (pipe_strc->size_redirec > 0)
    {
        if (!handle_redirections(pipe_strc))
        {
            if (size == 1)
                return ;
            else if (size > 1)
                exit(1);
        }
    }
    if (!pipe_strc->args)
        return ;
    cmd = pipe_strc->args[0];
    if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
        ft_cd_cmd(pipe_strc);
    else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
        ft_pwd_cmd();
    else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
        ft_echo(pipe_strc->args);
    else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
        ft_env_cmd();
    else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
        ft_exit(pipe_strc->args, pipe_strc->size_args);
    else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
        ft_unset(pipe_strc);
    else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
        ft_export(pipe_strc);
    close(1);
    dup2(std_out, 1);


    // dup2(0, 0);
}

void    exec_commad(t_AST *pipe_strc, char **env, int size)
{
    char *cmd_path;
    char *cmd;
    
    if (pipe_strc->size_redirec > 0)
    {
        if(!handle_redirections(pipe_strc))
        {
            if (size == 1)
                return ;
            else if (size > 1)
                exit(1);
        }
    }
    if (!pipe_strc->size_args)
        exit(0);
    if (pipe_strc->args[0][0] == 47)
        cmd = pipe_strc->args[0];
    else
        cmd = ft_strjoin(ft_strdup("/"), pipe_strc->args[0]);
    cmd_path = get_path(env, cmd);
    printf("command start in execve\n");
    if(execve(cmd_path, pipe_strc->args, env) == -1)
    {
        perror("minishell: ");
        exit(1);
    }
}

void    exec_simple_cmd(t_AST *pipe_strc, char **env, int nbre_pipes)
{

    if (pipe_strc->is_builten)
    {
        run_builtins(pipe_strc, nbre_pipes);
        if (nbre_pipes == 1)
            return ;
        else
            exit(0);
    }
    else if (nbre_pipes == 1)
    { 
        if (fork() == 0)
            exec_commad(pipe_strc, env, nbre_pipes);
        else
            wait(NULL);
    }
    else if (nbre_pipes > 1)
        exec_commad(pipe_strc, env, nbre_pipes);
    
}

void    exec_pipe_cmd(t_pipes *pipes, char **env)
{
    int i;
    int fd[2];
    int pid;
    int last_fd = -1;
    (void)env;

    // pipes->nbre_pipes--;
    i = -1;
    while (++i < pipes->nbre_pipes)
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
            if (i != pipes->nbre_pipes - 1)
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
            exec_simple_cmd(pipes->tab_cmd[i], env, pipes->nbre_pipes);
            // child process code end  
        }
        else
        {
            if (last_fd != -1)
                close(last_fd);
            last_fd = fd[0];
            close(fd[1]);
        }
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
        else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
            pipes->tab_cmd[i]->is_builten = 1;
        else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
            pipes->tab_cmd[i]->is_builten = 1;
        else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
            pipes->tab_cmd[i]->is_builten = 1;
        else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
            pipes->tab_cmd[i]->is_builten = 1;
        else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
            pipes->tab_cmd[i]->is_builten = 1;
        else
            pipes->tab_cmd[i]->is_builten = 0;
        i++;
    }
}

void    execution(t_pipes *pipes, char **env)
{   
    
    check_builtins(pipes);
    if (pipes->nbre_pipes == 1)
        exec_simple_cmd(pipes->tab_cmd[0], env , pipes->nbre_pipes);
    else if (pipes->nbre_pipes > 1)
        exec_pipe_cmd(pipes, env);
}

