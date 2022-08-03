/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:19:47 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/03 12:26:04 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

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

t_tocken	*get_string_dquote(t_lexer *lexer)
{
	char	*s;

	s = NULL;
	lexer_advance(lexer);
	if (!find_closed_qoute(lexer, '"'))
		return (ft_strdup("\""));
	while (lexer->c != '"' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == '$')
			return (get_string_dollar(lexer));
		else
			return (get_string_dqoute(lexer));
	}
}

char	*lexer_get_char_as_string(t_lexer *lexer)
{
	char	*s;

	s = malloc(2 * sizeof(char));
	if (!s)
		return (NULL);
	s[0] = lexer->c;
	s[1] = '\0';
	return (s);
}

t_tocken	*lexer_collect_string(t_lexer *lexer)
{
	char	*s;

	s = NULL;
	while (lexer->c)
	{
		if (lexer->c == '"')
			return (get_string_Dquote(lexer));
		if (lexer->c == '\'')
			return (get_string_Squote(lexer));
		if (lexer->c == '$')
			return (get_string_dollar(lexer));
		s = ft_strjoin_char(s, lexer->c);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	retrun (init_tocken(TOCKEN_WORD, s));
}

