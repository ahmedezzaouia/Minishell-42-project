/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 04:08:51 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/23 04:14:48 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"


void    ft_herdoc(t_pipes *ast)
{
    char *str;
	int	i;
	int j;

	i = 0;
	j = 0;
	str = NULL;
	while (i < ast->nbre_pipes)
	{
		j = 0;
		while (j < ast->tab_cmd[i]->size_redirec)
		{
			if (ast->tab_cmd[i]->redirec[j]->type == HERE_DOC)
			{
				if (pipe(ast->tab_cmd[i]->redirec[j]->heredoc) == -1)
				{
					printf("Error: \n");
    				exit(1);
				}
				while ((str = readline("> ")))
				{
					if (!str)
						break ;

					if (!ft_strncmp(str, ast->tab_cmd[i]->redirec[j]->filename, ft_strlen(ast->tab_cmd[i]->redirec[j]->filename)))
					{
						free(str);
						break ;
					}
					char *sh = ft_strjoin(str, "\n");
					ft_putstr_fd(sh, ast->tab_cmd[i]->redirec[j]->heredoc[1]);
					free(sh);
				}
				close(ast->tab_cmd[i]->redirec[j]->heredoc[1]);
				// only p[0] too get input from 
			}
			j++;
		}
		i++;
	}
}
