/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:20:56 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/28 09:43:38 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void    ft_print_error()
{
    printf("Error: \n");
    exit(1);
}

char    *get_path(char *cmd)
{
    int i;
    int j;
    char    **path_chunks;
    char    *cmd_joined_path;

    i = 0;
    path_chunks = ft_split(ft_get_env("PATH"), ':');
    
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
    // TODO:  :: you have to check if all path are not valid
    return (cmd);
}

void run_builtins(t_AST *pipe_strc, int size)
{
    
    int std_out;
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
                exit(g_data.exit_status);
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
}



void    handle_directory(char *cmd)
{
    DIR    *directory;
    
    directory = opendir(cmd);
    // printf("directory == %d\n", opendir(cmd));
    if (cmd[0] == '/' && !directory)
    {
        printf("minishell : %s : No such file or directory\n", cmd);
        g_data.exit_status = 1;
    }
    else if (directory && ft_strchr(cmd, '/'))
    {
        closedir(directory);
        printf("minishell : %s : Is a directory\n", cmd);
        g_data.exit_status = 126;
    }
    else if (!directory && ft_strchr(cmd, '/'))
    {
        printf("minishell : %s : Not a directory\n", cmd);
        g_data.exit_status = 1;
    }
    else
    {
        printf("minishell : %s : command not found\n", cmd);
        g_data.exit_status = 127;
    }
}

void    exec_commad(t_AST *pipe_strc, int size)
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
                exit(g_data.exit_status);
        }
    }
    if (!pipe_strc->size_args)
        exit(1);
    if (pipe_strc->args[0][0] == 47 || pipe_strc->args[0][0] == '.')
        cmd = pipe_strc->args[0];
    else
        cmd = ft_strjoin(ft_strdup("/"), pipe_strc->args[0]);
    cmd_path = get_path(cmd);
    printf("cmd path = %s\n",cmd_path);
    printf("command start in execve\n");
    if(execve(cmd_path, pipe_strc->args, g_data.env_list) == -1)
    {
        handle_directory(pipe_strc->args[0]);
        printf("status === %d\n", g_data.exit_status);
        exit(g_data.exit_status);
    }
}

void    exec_simple_cmd(t_AST *pipe_strc, int nbre_pipes)
{
    int pid;

    if (pipe_strc->is_builten)
    {
        run_builtins(pipe_strc, nbre_pipes);
        if (nbre_pipes == 1)
            return ;
        else
            exit(g_data.exit_status);
    }
    else if (nbre_pipes == 1)
    {
        pid = fork();
        if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            exec_commad(pipe_strc, nbre_pipes);
        }
        else
        {
            signal(SIGINT, SIG_IGN);
	        signal(SIGQUIT, SIG_IGN);
            if (pid)
            {
                waitpid(pid, &g_data.exit_status, 0);
                if (WIFEXITED(g_data.exit_status))
                    g_data.exit_status = WEXITSTATUS(g_data.exit_status);
                else if (g_data.exit_status == 3 || g_data.exit_status == 2)
                    g_data.exit_status += 128;
            }

            signal(SIGINT, sig_handler);
            signal(SIGQUIT, SIG_IGN);
        }
    }
    else if (nbre_pipes > 1)
        exec_commad(pipe_strc, nbre_pipes);
    
}

void sig_handler(int sig);

void    exec_pipe_cmd(t_pipes *pipes, char **env)
{
    int i;
    int fd[2];
    int pid;
    int last_fd = -1;
    (void)env;

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
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, sig_handler);
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
            exec_simple_cmd(pipes->tab_cmd[i], pipes->nbre_pipes);
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
    signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
    while (wait(NULL) != -1)
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
    // g_data.exit_status = WEXITSTATUS(g_data.exit_status); //WEXITSTATUS returns the exit status of the child process
	// if (WIFSIGNALED(g_data.exit_status)) // WIFSIGNALED returns true if the child process was terminated by a signal
	// 	g_data.exit_status = 128 + WTERMSIG(g_data.exit_status);
            
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
    close(fd[0]);
    close(fd[1]);
}

void init_builtins(t_pipes *pipes)
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

    g_data.is_child = 1;
    init_builtins(pipes);
    if (pipes->nbre_pipes == 1)
        exec_simple_cmd(pipes->tab_cmd[0], pipes->nbre_pipes);
    else if (pipes->nbre_pipes > 1)
        exec_pipe_cmd(pipes, env);

}

