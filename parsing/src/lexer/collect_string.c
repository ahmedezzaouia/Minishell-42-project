/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:19:47 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/04 22:26:58 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/*
	special characters
*/
int	diff_of_special_chars(char c)
{
	if (c != '<' && c != '>'
		&& c != '|' && c != '\t'
		&& c != ' ' && c != '\0')
		return (1);
	return (0);
}

/*
	looking for the next {"} || {'}
*/

int	find_closed_qoute(t_lexer *lexer, char c)
{
	int	i;

	i = lexer->i;
	while (lexer->contents[i] != '\0')
	{
		if (lexer->contents[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
	collect the character for Creating a string but becareful with
	some special characters like {'<', '>', '|', '\t', c != ' ', '\0'}
*/

t_tocken	*lexer_collect_string(t_lexer *lexer)
{
	char	*s;

	s = NULL;
	while (diff_of_special_chars(lexer->c))
	{
		if (lexer->c == '"')
			s = get_string_dquote(lexer);
		if (lexer->c == '\'')
			s = get_string_squote(lexer);
		else
		{
			s = ft_strjoin_char(s, lexer->c);
			if (s == NULL)
				ft_error(errno);
			lexer_advance(lexer);
		}
	}
	return (init_tocken(TOCKEN_WORD, s));
}

		// else if (lexer->c == '$')
		// 	s = get_string_dollar(lexer);