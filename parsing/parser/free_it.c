/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:11:00 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/27 02:24:14 by ahmaidi          ###   ########.fr       */
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
	int	i;

	i = -1;
	if (ast != NULL)
	{
		while (++i < ast->size_args)
			free(ast->args[i]);
		if (ast->args)
			free(ast->args);
		i = -1;
		while (++i < ast->size_redirec)
		{
			free(ast->redirec[i]->filename);
			free(ast->redirec[i]);
		}
		free(ast->redirec);
		free(ast);
	}
	return (NULL);
}

/* free pipe line */

t_pipes	*free_ast_pipe(t_pipes *pipes)
{
	int	i;

	i = -1;
	if (pipes != NULL)
	{
		while (++i < pipes->nbre_pipes)
			free_ast_cmd(pipes->tab_cmd[i]);
		free(pipes->tab_cmd);
		free(pipes);
	}
	return (NULL);
}

/* free the tab of args in simple cmd with ambigous direct */

void	free_args_in_ambg_cas(t_AST **ast, t_parser **parser)
{
	int	i;

	i = -1;
	if ((*parser)->lex_ambg)
	{
		if ((*ast)->size_args > 0)
		{
			while (++i < (*ast)->size_args)
				free((*ast)->args[i]);
		}
		(*ast)->size_args = 0;
	}
	(*parser)->lex_ambg = 0;
}