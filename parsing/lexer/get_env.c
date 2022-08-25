/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:29:20 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/25 03:26:08 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

char	*ft_get_env(char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (!s || !g_data.env_list || !*(g_data.env_list))
		return (NULL);
	while (g_data.env_list[i])
	{
		if ((!ft_strncmp(s, g_data.env_list[i], ft_strlen(s)))
			&& (g_data.env_list[i][ft_strlen(s)] == '='))
		{
			str = ft_substr(g_data.env_list[i], ft_strlen(s) + 1,
					ft_strlen(g_data.env_list[i]) - ft_strlen(s));
			if (!str)
				ft_error(errno);
			break ;
		}
		i++;
	}

	return (str);
}
