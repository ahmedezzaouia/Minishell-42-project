/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:32:24 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/14 19:30:05 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	visitor_command(t_AST *pipe)
{
	int	i;

	i = 0;
	while (i < pipe->size_args)
	{
		printf("COMMAND(%s)\n", pipe->args[i]);
		i++;
	}
	i = 0;
	while (i < pipe->size_redirec)
	{
		printf("redirection (type : %d, value :%s)\n", pipe->redirec[i]->type,
			pipe->redirec[i]->filename);
		i++;
	}
}

static void	visitor_pipeline(t_AST *ast)
{
	int	i;

	printf("---------pipeline------\n");
	i = 0;
	while (i < ast->pipe_size)
	{
		printf("The PIPE nbre of %d\n", i);
		visitor_command(ast->pipe[i]);
		i++;
	}
}

int	visitor_vis(t_AST *ast)
{
	visitor_pipeline(ast);
	return (0);
}
