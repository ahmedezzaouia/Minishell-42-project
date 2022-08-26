/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 06:33:54 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/25 12:01:23 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/parsing.h"

void    ft_pwd_cmd()
{
    // int i;
    char *s;
    
    // char *s;

    // i = 0;
    // while (g_data.env_list[i] && ft_strncmp(g_data.env_list[i], "PWD=",4))
    //     i++;
    s = getcwd(NULL, 0);
    printf("%s\n", s);
    free (s);
    // s = getcwd(NULL, 0);
    // if (!s)
    //     printf("%s\n", getenv("PWD")); 
    // else 
    //     printf("%s\n", s); 
    // free(s);
    // fprintf(stderr, "%s\n",getcwd(s, 100));
    
        
}
