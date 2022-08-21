/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:29:51 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/21 02:30:56 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
  
// chdir function is declared
// inside this header
#include<unistd.h> 
#include<unistd.h> 
int main()
{   
    char s[100];
  
    // printing current working directory
    printf("%s\n", getcwd(s, 100));
  
    // using the command
    chdir("..");
  
    // printing current working directory
    printf("%s\n", getcwd(s, 100));
  
    // after chdir is executed
    return 0;
}
