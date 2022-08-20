/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string_dqoute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:33:29 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/19 22:28:59 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/*
	collect a string between double quote
*/

void	lexer_get_string_dqoute(t_lexer *lexer, char **s)
{
	int		start;
	int		end;
	char	*tmp;

	start = lexer->i;
	while (lexer->c != '"' && lexer->c != '$' && lexer->c != '\0')
		lexer_advance(lexer);
	end = lexer->i;
	if (lexer->c == '\0')
		return ;
	tmp = ft_substr(lexer->contents, start, end - start);
	if (tmp == NULL)
		ft_error(errno);
	*s = ft_strjoin(*s, tmp);
	free(tmp);
	if (*s == NULL)
		ft_error(errno);
}

/*
	collect a string between double quote And 
	expand if there env Variable or exit status next to $ between them.
*/

char	*get_string_dquote(t_lexer *lexer)
{
	char	*s;

	lexer_advance(lexer);
	if (!find_closed_qoute(lexer, '"'))
	{
		write(2, "Minishell: Missing close double qoute\n", 39);
		g_exit_status = 258;
		return (NULL);
	}
	s = ft_strdup_er("");
	while (lexer->c != '"' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == '$')
			lexer_collect_string_dollar(lexer, &s);
		else
			lexer_get_string_dqoute(lexer, &s);
	}
	lexer_advance(lexer);
	return (s);
}
