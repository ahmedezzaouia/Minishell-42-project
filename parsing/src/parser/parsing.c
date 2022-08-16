/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:08:55 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/16 02:23:52 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	get_ast_pipeline(t_parser *parser, t_AST **ast)
{
	t_AST	*simple_cmd;

	parser_expected(parser, TOCKEN_PIPE);
	simple_cmd = get_ast_simple_cmd(parser);
	if (!simple_cmd)
	{
		if (ast)
			free_ast_pipe(*ast);
		*ast = NULL;
		return ;
	}
	(*ast)->pipe = ft_realloc_er((*ast)->pipe, sizeof(t_AST **),
			(*ast)->pipe_size);
	(*ast)->pipe_size += 1;
	(*ast)->pipe[(*ast)->pipe_size - 1] = simple_cmd;
}

t_AST	*parser_parse(t_parser *parser)
{
	t_AST	*t;
	t_AST	*ast_simple_cmd;

	ast_simple_cmd = get_ast_simple_cmd(parser);
	if (!ast_simple_cmd)
		return (NULL);
	t = init_ast(PIPELINE);
	t->pipe = malloc(sizeof(t_AST *));
	if (t->pipe == NULL)
		ft_error(errno);
	t->pipe[0] = ast_simple_cmd;
	t->pipe_size += 1;
	while (t && parser->cur_tocken && parser->cur_tocken->type == TOCKEN_PIPE)
		get_ast_pipeline(parser, &t);
	return (t);
}
