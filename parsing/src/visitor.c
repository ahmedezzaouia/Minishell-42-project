/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:32:24 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/17 23:21:16 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	visitor_command(t_AST *pipe)
{
	int	i;

	i = 0;
	printf("\033[35m********** ARG ***************\033[0m\n");
	printf("\033[35m********** size = %d **********\033[0m\n", pipe->size_args);
	while (i < pipe->size_args)
	{
		printf("ARG[%d] = %s\n", i,pipe->args[i]);
		i++;
	}
	printf("\033[35m*******************************\033[0m\n");
	i = 0;
	printf("\033[37m++++++++++ REDIRECTIONS +++++++++++++\033[0m\n");
	printf("\033[37m++++++++++ size = %d ++++++++++++++++\033[0m\n", pipe->size_redirec);
	while (i < pipe->size_redirec)
	{
		printf("redirection (type : %d, value :%s)\n", pipe->redirec[i]->type,
			pipe->redirec[i]->filename);
		i++;
	}
	printf("\033[37m+++++++++++++++++++++++++++++++++++++\033[0m\n");
}

static void	visitor_pipeline(t_pipes *ast)
{
	int	i;

	printf("\033[92m--------- pipeline ------\033[0m\n");
	printf("\033[92m--------- Size = %d --------\033[0m\n", ast->nbre_pipes);
	i = 0;
	while (i < ast->nbre_pipes)
	{
		printf("\033[93m############ The PIPE nbre of %d ############\033[0m\n", i);
		visitor_command(ast->tab_cmd[i]);
		printf("\033[93m##############################################\033[0m\n");
		i++;
	}
}

int	visitor(t_pipes *ast)
{
	if (ast)
		visitor_pipeline(ast);
	return (0);
}
