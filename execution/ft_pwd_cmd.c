/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 06:33:54 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/29 22:35:44 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	ft_pwd_cmd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (s != NULL)
		printf("%s\n", s);
	else
	{
		s = ft_get_env("PWD");
		if (!s)
			printf("%s\n", g_data.pwd);
		else
			printf("%s\n", s);
	}
	free (s);
}
