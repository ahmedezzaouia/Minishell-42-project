/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:33:37 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/21 03:34:36 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/parsing.h"

void    ft_cd_cmd(t_AST *cmd_strc)
{
    int i;

    i = 1;
    while ((i < cmd_strc->size_args) && (cmd_strc->args[i][0] == 45))
        i++;
    if (cmd_strc->size_args == 1)
    {
        // printf("getenv(HOME) === %s\n", getenv("HOME"));
        chdir(getenv("HOME"));
    }
    else
        chdir(cmd_strc->args[i]);
         
}
