/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:06:13 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/19 02:15:08 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	fill_args(char ***args, char **str, int *size)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(*str, ' ');
	if (!split)
		ft_error(errno);
	while (split[i])
	{
		*args = ft_realloc_er(*args, sizeof(char *), *size);
		*size += 1;
		(*args)[*size - 1] = split[i];
		i++;
	}
	free(split);
	free(*str);
}
