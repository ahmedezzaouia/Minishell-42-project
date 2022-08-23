/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:33:37 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/23 21:05:06 by ahmez-za         ###   ########.fr       */
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
    while (g_data.env_list[i] && ft_strncmp(g_data.env_list[i], "OLDPWD=",4))
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
    // char *str;
    // char **split_path;
    char *pwd;
    char *s;

    pwd = g_data.env_list[get_pwd_index()];
    
    if (!g_data.env_list[get_oldpwd_index()])
    {
        g_data.env_list = ft_realloc_er(g_data.env_list, sizeof(char *), get_env_list_size() + 1);
        g_data.env_list[get_env_list_size()] = ft_strjoin(ft_strdup("OLD"), pwd);
        g_data.env_list[get_env_list_size() + 1] = NULL;
    }
    else
        g_data.env_list[get_oldpwd_index()] = ft_strjoin(ft_strdup("OLD"), pwd);

    i = 1;
    while ((i < cmd_strc->size_args) && (cmd_strc->args[i][0] == 45))
        i++;

    if (cmd_strc->args[i] == NULL && i != 1)
        return ;
    if (cmd_strc->size_args == 1)
    {
        // printf("getenv(HOME) === %s\n", getenv("HOME"));
        if (chdir(getenv("HOME")) == -1)
            perror("Minishell :");
    }
    else
    {

        if (chdir(cmd_strc->args[i]) == -1)
        {
            // printf("cd error\n");
            // g_data.env_list[get_pwd_index()] = ft_strjoin(pwd, ft_strjoin(ft_strdup("/"),cmd_strc->args[i]));
            perror("Minishell :");
        }
        else
        {
            s = getcwd(NULL, 0);
            printf("cwd = %s\n",s);
            printf("pwd == %s\n",pwd);
            if (s == NULL)
            {
                // g_data.env_list[get_pwd_index()] = s;
                // error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
                printf("Minishell : error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
                g_data.env_list[get_pwd_index()] = ft_strjoin(ft_strdup(g_data.env_list[get_pwd_index()]), ft_strjoin(ft_strdup("/"), cmd_strc->args[i]));
            }
            else
            {   
                printf("**************** cwd else ********\n");
                g_data.env_list[get_pwd_index()] = ft_strjoin(ft_strdup("PWD="), s);
                printf("cwd after == %s\n",s);

            }



            // printf("g_data.env_list[i] == %s\n", g_data.env_list[get_pwd_index()]);
            // ft_strcmp(cmd_strc->args[i], "..", 2)
            // printf("else cd run\n");
            // if (!getcwd(NULL, 0))
            // {
            //     g_data.env_list[get_pwd_index()] = ft_strjoin(ft_strdup(pwd), \
            //                     ft_strjoin(ft_strdup("/"), cmd_strc->args[i]));
            // }
            // else
                // g_data.env_list[get_pwd_index()] = ft_strjoin(ft_strdup(pwd), \
                //                 ft_strjoin(ft_strdup("/"), cmd_strc->args[i]));
            // printf("%s\n",pwd);
            // printf("%s\n",cmd_strc->args[i]);
        }
    }
         
}
