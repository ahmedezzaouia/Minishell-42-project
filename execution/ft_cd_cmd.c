/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:33:37 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/21 05:22:25 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/parsing.h"

void    ft_cd_cmd(t_AST *cmd_strc)
{
    int i;

    i = 1;
    while ((i < cmd_strc->size_args) && (cmd_strc->args[i][0] == 45))
        i++;
    printf("cmd_strc->args[i] == %s\n",cmd_strc->args[i]);
    printf("i === %d\n",i);
    printf("cmd_strc->size_args == %d\n",cmd_strc->size_args);
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
        printf("chdir work------ with i = %d\n",i);
        if (chdir(cmd_strc->args[i]) == -1)
            perror("Minishell :");
    }
         
}
