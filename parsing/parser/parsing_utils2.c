/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 20:19:39 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/26 23:40:45 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/* collect the arg in the table of args*/
void	collect_args(t_parser *parser, t_AST *ast)
{
	while (parser->cur_tocken && parser->cur_tocken->type == TOCKEN_WORD)
	{
		if (parser->lexer->env_vide)
		{
			parser_expected(parser, TOCKEN_WORD);
			continue ;
		}
		if (parser->lexer->split_lexer)
		{
			fill_args(&(ast->args), &parser->cur_tocken->value,
				&(ast->size_args));
			parser_expected(parser, TOCKEN_WORD);
			if (parser->cur_tocken->type != TOCKEN_WORD)
				break ;
		}
		ast->args = ft_realloc_er(ast->args, sizeof(char *),
				ast->size_args);
		ast->size_args += 1;
		ast->args[ast->size_args - 1] = parser->cur_tocken->value;
		parser_expected(parser, TOCKEN_WORD);
	}
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
/*Allocate the redirections tab */

void	alloc_redirec(t_AST *ast)
{
	ast->redirec = ft_realloc_er(ast->redirec, sizeof(t_redir *),
			ast->size_redirec);
	ast->size_redirec += 1;
	ast->redirec[ast->size_redirec - 1] = malloc(sizeof(t_redir));
	if (ast->redirec[ast->size_redirec - 1] == NULL)
		ft_error(errno);
}

/* Check ambigous redirect */
int	check_ambiguous(int status)
{
	if (status)
	{
		write(2, "Minishell: ambiguous redirect\n", 31);
		g_data.exit_status = 1;
		return (1);
	}
	return (0);
}

/* Collect the filename of redirections */
int	collect_redirect(t_parser *parser, t_AST *ast)
{
	t_type_redir	type;
	int				index_c;

	index_c = parser->lexer->i;
	type = get_type_redirect(parser);
	parser_expected(parser, parser->cur_tocken->type);
	if (parser->lexer->is_ambg && !parser->lex_ambg)
		parser->lex_ambg = parser->lexer->is_ambg;
	if (type != HERE_DOC && (check_ambiguous(parser->lexer->is_ambg)
			|| parser->lex_ambg))
	{
		parser_expected(parser, parser->cur_tocken->type);
		if (parser->prev_tocken)
			free(parser->prev_tocken->value);
		return (0);
	}
	if (parser_expected(parser, TOCKEN_WORD))
		return (1);
	alloc_redirec(ast);
	if (type == HERE_DOC)
		analyse_here_doc(parser, &type, index_c);
	ast->redirec[ast->size_redirec - 1]->type = type;
	ast->redirec[ast->size_redirec - 1]->filename = parser->prev_tocken->value;
	return (0);
}
