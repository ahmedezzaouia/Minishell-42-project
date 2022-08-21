/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:24:25 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/21 16:40:47 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	env_variable(char***env_list, char **env)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (env[i] != NULL)
	{
		(*env_list) = ft_realloc_er((*env_list), sizeof(char *), size);
		size += 1;
		(*env_list)[size - 1] = env[i];
		i++;
	}
	(*env_list) = ft_realloc_er((*env_list), sizeof(char *), size);
		size += 1;
	(*env_list)[size - 1] = NULL;
}
