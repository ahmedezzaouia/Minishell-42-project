/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:08:55 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/09 18:20:09 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

t_AST	*parser_parse(t_parser *parser)
{
	t_AST	*ast_simple_cmd;

	ast_simple_cmd = get_ast_simple_cmd(parser);
	if (!ast_simple_cmd)
		rerturn (NULL);
	
}
