/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:08:55 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/26 23:19:48 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	get_ast_pipeline(t_parser *parser, t_pipes **pipes)
{
	t_AST	*ast_simple_cmd;

	parser_expected(parser, TOCKEN_PIPE);
	ast_simple_cmd = get_ast_simple_cmd(parser);
	if (!ast_simple_cmd)
	{
		if (pipes)
			free_ast_pipe(*pipes);
		*pipes = NULL;
		return ;
	}
	if (ast_simple_cmd->size_args != 0 || ast_simple_cmd->size_redirec != 0)
	{
		(*pipes)->tab_cmd = ft_realloc_er((*pipes)->tab_cmd, sizeof(t_AST **),
				(*pipes)->nbre_pipes);
		(*pipes)->nbre_pipes += 1;
		(*pipes)->tab_cmd[(*pipes)->nbre_pipes - 1] = ast_simple_cmd;
	}
	else
		free_ast_cmd(ast_simple_cmd);
}

t_pipes	*parser_parse(t_parser *parser)
{
	t_pipes	*pipes;
	t_AST	*ast_simple_cmd;

	ast_simple_cmd = get_ast_simple_cmd(parser);
	if (!ast_simple_cmd)
		return (NULL);
	pipes = malloc(sizeof(t_pipes));
	if (pipes == NULL)
		ft_error(errno);
	pipes->tab_cmd = malloc(sizeof(t_AST *));
	if (pipes->tab_cmd == NULL)
		ft_error(errno);
	pipes->nbre_pipes = 0;
	if (ast_simple_cmd->size_args != 0 || ast_simple_cmd->size_redirec != 0)
	{
		pipes->tab_cmd[0] = ast_simple_cmd;
		pipes->nbre_pipes += 1;
	}
	else
		free_ast_cmd(ast_simple_cmd);
	while (pipes && parser->cur_tocken
		&& parser->cur_tocken->type == TOCKEN_PIPE)
		get_ast_pipeline(parser, &pipes);
	return (pipes);
}
