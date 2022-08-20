/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:11:00 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/20 19:08:04 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/* free Tocken */
void	free_tocken(t_tocken *tocken)
{
	if (tocken != NULL)
	{
		if (tocken->type != TOCKEN_WORD)
		{
			if (tocken->value)
				free(tocken->value);
		}
		if (tocken)
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
		if (parser->prev_tocken)
			free_tocken(parser->prev_tocken);
		if (parser->cur_tocken)
			free_tocken(parser->cur_tocken);
		if (parser)
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
		if (ast->redirec)
			free(ast->redirec);
		if (ast)
			free(ast);
	}
	return (NULL);
}

/* free pipe line */

t_pipes	*free_ast_pipe(t_pipes *pipes)
{
	if (pipes != NULL)
	{
		while (pipes->nbre_pipes-- > 0)
		{
			free_ast_cmd(pipes->tab_cmd[pipes->nbre_pipes]);
		}
		if (pipes->tab_cmd)
			free(pipes->tab_cmd);
		if (pipes)
			free(pipes);
	}
	return (NULL);
}
