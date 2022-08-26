/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_args_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 16:31:52 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/25 16:39:24 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

char	*filling_args_export(char *str)
{
	int		i;
	char	*s;

	s = NULL;
	i = 0;
	if (ft_strchr(str, '+'))
	{
		s = ft_strdup_er("");
		while (str[i])
		{
			if (str[i] == '+')
			{
				i++;
				continue ;
			}
			s = ft_strjoin_char(s, str[i]);
			if (!s)
				ft_error(errno);
			i++;
		}
		return (s);
	}
	else
		return (ft_strdup_er(str));
}
