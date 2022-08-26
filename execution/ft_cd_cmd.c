/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:33:37 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/26 02:38:14 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/parsing.h"


int     get_pwd_index()
{
    int i;
    
    i = 0;
    while (g_data.env_list[i] && ft_strncmp(g_data.env_list[i], "PWD=",4))
        i++;
    return (i);
}

int     get_oldpwd_index()
{
    int i;
    
    i = 0;
    while (g_data.env_list[i] && ft_strncmp(g_data.env_list[i], "OLDPWD=",7))
        i++;
    return (i);
}


void    go_to_home(char *s)
{
    char *item;
    item = NULL;
    if (chdir(ft_get_env("HOME")) == -1)
        perror("Minishell :");
    else
    {

        /* TODO: update The pwd on case one arg (cd) */
        // free(item);
        item = g_data.env_list[get_pwd_index()];
        s = getcwd(NULL, 0);
        g_data.env_list[get_pwd_index()] = ft_strjoin(ft_strdup("PWD="), s);
        printf("s == %s\n",s);
        free(item);
        free(s);
    }
}

void    update_old_Pwd(char *pwd)
{
    int oldpwdindex;
    char *item;
    
    oldpwdindex = get_oldpwd_index();

    if (g_data.env_list[oldpwdindex] == NULL)
    {
        g_data.env_list = ft_realloc_er(g_data.env_list, sizeof(char *), g_data.size_env_list + 1);
        g_data.env_list[g_data.size_env_list] = ft_strjoin(ft_strdup("OLD"), pwd);
        g_data.env_list[g_data.size_env_list + 1] = NULL;
    }
    else
    {
        item = g_data.env_list[oldpwdindex]; 
        g_data.env_list[get_oldpwd_index()] = ft_strjoin(ft_strdup("OLD"), pwd);
        free(item);
    }
}

void    change_dir(t_AST *cmd_strc, char *s, char *str_join, char *pwd)
{
    char *item;

    item = NULL;
    s = getcwd(NULL, 0);
    if (s == NULL)
        {
            item =  g_data.env_list[get_pwd_index()];
            printf("Minishell : error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
            str_join = ft_strjoin(ft_strdup("/"), cmd_strc->args[1]);
            g_data.env_list[get_pwd_index()] = ft_strjoin(ft_strdup(pwd),str_join);
            free(item);
            free(str_join);
        }
    else
        {   
            item = g_data.env_list[get_pwd_index()];
            g_data.env_list[get_pwd_index()] = ft_strjoin(ft_strdup("PWD="), s);
            free(item);
        }
    free(s);
}

void    ft_cd_cmd(t_AST *cmd_strc)
{
    char *str_join;
    char *pwd;
    char *s;
    char *item;

    s = NULL;
    item = NULL;
    str_join = NULL;
    pwd = g_data.env_list[get_pwd_index()];
    update_old_Pwd(pwd);
    if (cmd_strc->size_args == 1)
        go_to_home(s);
    else
    {
        if (chdir(cmd_strc->args[1]) == -1)
            perror("Minishell :");
        else
            change_dir(cmd_strc, s, str_join, pwd);
    }
    free (s);

}
