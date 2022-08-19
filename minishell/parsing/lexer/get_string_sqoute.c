/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string_sqoute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:46:38 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/17 15:38:21 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/* get the string between the Single Quotes*/
char	*get_string_squote(t_lexer *lexer)
{
	char	*s;
	int		start;
	int		ends;

	lexer_advance(lexer);
	if (!find_closed_qoute(lexer, '\''))
	{
		write(2, "Minishell: Missing close single qoute\n", 39);
		g_exit_status = 258;
		return (NULL);
	}
	start = lexer->i;
	while (lexer->c != '\'' && lexer->c != '\0')
		lexer_advance(lexer);
	ends = lexer->i;
	s = ft_substr(lexer->contents, start, ends - start);
	if (!s)
		ft_error(errno);
	lexer_advance(lexer);
	return (s);
}
