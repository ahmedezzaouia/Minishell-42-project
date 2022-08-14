/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:11:00 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/14 19:19:17 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/* free Tocken */
void	free_tocken(t_tocken *tocken)
{
	if (tocken != NULL)
	{
		if (tocken->type != TOCKEN_WORD)
			free(tocken->value);
		free(tocken);
	}
}

/* free a parser */

void	free_parser(t_parser *parser)
{
	if (parser != NULL)
	{
		if (parser->lexer != NULL)
		{
			free(parser->lexer->contents);
			free(parser->lexer);
		}
		free_tocken(parser->prev_tocken);
		free_tocken(parser->cur_tocken);
		free(parser);
	}
}

/* free ast NODE*/
t_AST	*free_ast_cmd(t_AST *ast)
{
	if (ast != NULL)
	{
		while (ast->size_args-- > 0)
			free(ast->args[ast->size_args]);
		free(ast->args);
		while (ast->size_redirec -- > 0)
		{
			free(ast->redirec[ast->size_redirec]->filename);
			free(ast->redirec[ast->size_redirec]);
		}
		free(ast->redirec);
		free(ast);
	}
	return (NULL);
}

/* free pipe line */

t_AST	*free_ast_pipe(t_AST *ast)
{
	if (ast != NULL)
	{
		while (ast->pipe_size-- > 0)
			free_ast_cmd(ast->pipe[ast->pipe_size]);
		free(ast->pipe[ast->pipe_size]);
		free(ast);
	}
	return (NULL);
}
