/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:06:28 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/19 01:57:29 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static char	*get_string_quote(t_lexer *lexer)
{
	char	*str;

	if (lexer->c == '\'')
		str = get_string_squote(lexer);
	else
		str = get_string_dquote(lexer);
	return (str);
}

static	void	check_error(char *s)
{
	if (s == NULL)
		ft_error(errno);
}

char	*get_string_dollar(t_lexer	*lexer)
{
	char	*s;
	char	*str;

	s = ft_strdup_er("");
	lexer_advance(lexer);
	if (lexer->c == '?')
		str = get_value_exit(lexer);
	else if (lexer->c == '\'' || lexer->c == '"')
		str = get_string_quote(lexer);
	else if (lexer->c != '_' && !ft_isalpha(lexer->c))
	{
		str = ft_substr(lexer->contents, lexer->i - 1, 2);
		if (!str)
			ft_error(errno);
		lexer_advance(lexer);
	}
	else
		str = get_env_variable(lexer, 1);
	if (!str)
		return (NULL);
	s = ft_strjoin(s, str);
	if (ft_strlen(str) >= 0)
		free(str);
	check_error(s);
	return (s);
}
