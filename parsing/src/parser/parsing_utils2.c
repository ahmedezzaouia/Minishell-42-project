/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 20:19:39 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/09 18:33:58 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/* free the tocken */
void	free_tocken(t_tocken *tocken)
{
	if (tocken != NULL)
	{
		free(tocken->value);
		free(tocken);
	}
}

/* collect the arg in the table of args*/
void	collect_args(t_parser *parser, t_AST *ast)
{
	while (parser->cur_tocken->type == TOCKEN_WORD)
	{
		ast->args = ft_realloc_er(ast->args, sizeof(char *), ast->size_args);
		ast->size_args += 1;
		ast->args[ast->size_args - 1] = parser->cur_tocken;
		free_tocken(parser->prev_tocken);
		parser->prev_tocken = parser->cur_tocken;
		parser->cur_tocken = lexer_get_next_tocken(parser->lexer);
	}
	ast->args = ft_realloc_er(ast->args, sizeof(char *), ast->size_args);
	ast->args[ast->size_args] = NULL;
}

/* get the type of redirect */
t_type_redir	get_type_redirect(t_parser *parser)
{
	if (parser->cur_tocken->type == TOCKEN_GREAT)
		return (OUTPUT);
	else if (parser->cur_tocken->type == TOCKEN_LESS)
		return (INPUT);
	else if (parser->cur_tocken->type == TOCKEN_DGREAT)
		return (APPAND);
	else
		return (HERE_DOC);
}

/* Collect the filename of redirections */
int	collect_redirect(t_parser *parser, t_AST *ast)
{
	t_type_redir	type;

	type = get_type_redirect(parser);
	parser_expected(parser, type);
	if (parser_expected(parser, TOCKEN_WORD))
		return (1);
	ast->redirec = ft_realloc_re(ast->redirec, sizeof(t_redir *),
			ast->size_redirec);
	ast->size_redirec += 1;
	ast->redirec[ast->size_redirec - 1]->filename = malloc(ft_strlen(parser->cur_tocken->value));
}
