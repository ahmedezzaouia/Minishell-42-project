/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 06:33:54 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/21 16:07:34 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/parsing.h"

void    ft_pwd_cmd()
{
    char s[100];

    if (!getcwd(s, 100))
        printf("%s\n", getenv("PWD")); 
    else 
        printf("%s\n", getcwd(s, 100)); 

        
    // fprintf(stderr, "%s\n",getcwd(s, 100));
        
}
