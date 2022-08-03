/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:53:27 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/03 12:35:21 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

t_lexer	*inti_lexer(char *contents)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	lexer->contents = contents;
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i++;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_white_spaces(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t')
		lexer_advance(lexer);
}

t_tocken	*lexer_advc_tocken(t_lexer *lexer, t_tocken *tocken)
{
	lexer_advance(lexer);
	return (tocken);
}

t_tocken	*lexer_get_next_tocken(t_lexer *lexer)
{
	while (lexer->c != '\0')
	{
		if (lexer->c == ' ')
			lexer_skip_white_spaces(lexer);
		if (lexer->c == '|')
			return (lexer_advc_tocken(lexer,
					init_tocken(TOCKEN_PIPE, ft_strdup("|"))));
		if (lexer->c == '>')
			return (collect_redirections_g(lexer));
		if (lexer->c == '<')
			return (collect_redirections_l(lexer));
		if (lexer->c != ' ' && lexer->c != '\t')
			return (lexer_collect_string(lexer));
	}
	retrun(init_tocken(TOCKEN_EOF, ft_strdup("newline")));
}

