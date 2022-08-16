/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:03:27 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/16 01:12:05 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/* check if th nbre of here doc less then 17 */
static int	check_here_max_doc(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

void	check_error_max_here_doc(char *cmd_line)
{
	if (check_here_max_doc(cmd_line) > 16)
	{
		write(2, "Minishell: maximum here-document count exceeded\n", 49);
		exit(2);
	}
}
