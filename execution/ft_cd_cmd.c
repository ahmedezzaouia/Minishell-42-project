/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:33:37 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/24 03:41:40 by ahmez-za         ###   ########.fr       */
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

int get_env_list_size()
{
    int i;

    i = 0;
    while (g_data.env_list[i])
        i++;
    return (i);
}

void    ft_cd_cmd(t_AST *cmd_strc)
{
    int i;
    int len;
    // char *str;
    // char **split_path;
    char *pwd;
    char *s;
    char *item;


    s = NULL;
    item = NULL;


    len = get_env_list_size();
    pwd = g_data.env_list[get_pwd_index()];
    int oldpwdindex = get_oldpwd_index();
    printf("oldpwd index === %d\n",oldpwdindex);
    printf("oldpwd == %s\n", g_data.env_list[get_oldpwd_index()]);
    if (g_data.env_list[oldpwdindex] == NULL)
    {
        g_data.env_list = ft_realloc_er(g_data.env_list, sizeof(char *), len + 1);
        g_data.env_list[len] = ft_strjoin(ft_strdup("OLD"), pwd);
        g_data.env_list[len + 1] = NULL;
    }
    else
    {
        // ft_sanitize here 
        item = g_data.env_list[oldpwdindex]; 
        g_data.env_list[get_oldpwd_index()] = ft_strjoin(ft_strdup("OLD"), pwd);
        free(item);
    }
    i = 1;
    while ((i < cmd_strc->size_args) && (cmd_strc->args[i][0] == 45))
        i++;

    if (cmd_strc->args[i] == NULL && i != 1)
        return ;
    if (cmd_strc->size_args == 1)
    {

        if (chdir(getenv("HOME")) == -1)
            perror("Minishell :");
        else
        {

            /* TODO: update The pwd on case one arg (cd) */
            // free(item);
            item = g_data.env_list[get_pwd_index()];
            s = getcwd(NULL, 0);
            // printf("getCwd == %s\n",getcwd(NULL, 0));s
            g_data.env_list[get_pwd_index()] = ft_strjoin(ft_strdup("PWD="), s);
            free(item);
        }
    }
    else
    {
        

        if (chdir(cmd_strc->args[i]) == -1)
            perror("Minishell :");
        else
        {
            // item = g_data.env_list[get_pwd_index()];
            s = getcwd(NULL, 0);
            printf("pwd == %s\n",pwd);
            printf("cwd = %s\n",s);
            if (s == NULL)
            {
                printf("Minishell : error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
                g_data.env_list[get_pwd_index()] = ft_strjoin(ft_strdup(pwd), ft_strjoin(ft_strdup("/"), cmd_strc->args[i]));

            }
            else
            {   
                // printf("**************** cwd else ********\n");
                item = g_data.env_list[get_pwd_index()];
                g_data.env_list[get_pwd_index()] = ft_strjoin(ft_strdup("PWD="), s);
                free(item);
                // free(g_data.env_list[get_pwd_index()]);
                // printf("cwd after == %s\n",s);
                // free(tmp);

            }
            // free(tmp);
        }
    }
    free (s);

}
