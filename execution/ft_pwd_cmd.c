/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 06:33:54 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/09/01 18:12:46 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	ft_pwd_cmd(void)
{
	char	*s;
	
	s = getcwd(NULL, 0);
	if (s)
		g_data.pwd = ft_strdup(s);
	if (s != NULL)
		printf("%s\n", s);
	else
		printf("%s\n", g_data.pwd);
	free (s);
}
