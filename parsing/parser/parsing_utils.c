/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:54:46 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/21 18:17:31 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/* initialize the parser */
t_parser	*init_parser(char *cmd)
{
	t_lexer		*lexer;
	t_parser	*parser;

	parser = ft_calloc(1, sizeof(t_parser));
	if (!parser)
		ft_error(errno);
	lexer = init_lexer(cmd);
	if (!lexer)
		ft_error(errno);
	parser->lexer = lexer;
	parser->cur_tocken = lexer_get_next_tocken(lexer);
	parser->prev_tocken = NULL;
	return (parser);
}
/* initialize the AST */

t_AST	*init_ast(void)
{
	t_AST	*ast;

	ast = malloc(1 * sizeof(t_AST));
	if (!ast)
		ft_error(errno);
	ast->args = NULL;
	ast->size_args = 0;
	ast->redirec = NULL;
	ast->size_redirec = 0;
	return (ast);
}

/* Check if there any unexpected tocken */

int	parser_expected(t_parser *parser, t_tocken_type type)
{
	if (parser->cur_tocken)
	{
		if (parser->cur_tocken->type == type)
		{
			if (parser->lexer->env_vide
				&& not_redirect(parser->prev_tocken))
				free(parser->cur_tocken->value);
			free_tocken(parser->prev_tocken);
			parser->prev_tocken = parser->cur_tocken;
			parser->cur_tocken = lexer_get_next_tocken(parser->lexer);
			return (0);
		}
		write(2, "Minishell: syntax error near unexpected token `", 48);
		write(2, parser->cur_tocken->value,
			ft_strlen(parser->cur_tocken->value));
		write(2, "'\n", 2);
		g_data.exit_status = 258;
	}
	return (1);
}

/* Syntax Error */
int	check_syntax_cmd(t_parser *parser)
{
	if (!parser->cur_tocken)
		return (1);
	if (parser->cur_tocken->type == TOCKEN_PIPE
		|| parser->cur_tocken->type == TOCKEN_EOF)
		return (parser_expected(parser, TOCKEN_WORD));
	return (0);
}

/* fill the node by Simple Commande */

t_AST	*get_ast_simple_cmd(t_parser *parser)
{
	t_AST	*ast;

	if (check_syntax_cmd(parser))
		return (NULL);
	ast = init_ast();
	while (parser->cur_tocken && parser->cur_tocken->type != TOCKEN_PIPE
		&& parser->cur_tocken->type != TOCKEN_EOF)
	{
		if (parser->cur_tocken->type == TOCKEN_WORD)
			collect_args(parser, ast);
		else if (collect_redirect(parser, ast))
			return (free_ast_cmd(ast));
	}
	if (!parser->cur_tocken)
	{
		free_ast_cmd(ast);
		return (NULL);
	}
	if (ast->args)
	{
		ast->args = ft_realloc_er(ast->args, sizeof(char *), ast->size_args);
		ast->args[ast->size_args] = NULL;
	}
	return (ast);
}
