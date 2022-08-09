/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_simple_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 16:38:42 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/09 15:15:12 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/* get the string between the Simple String*/
char	*get_simple_chars(t_lexer *lexer)
{
	char	*s;
	int		start;
	int		ends;

	start = lexer->i;
	while (diff_of_special_chars(lexer->c) && lexer->c != '"'
		&& lexer->c != '\'' )
		lexer_advance(lexer);
	ends = lexer->i;
	s = ft_substr(lexer->contents, start, ends - start);
	if (!s)
		ft_error(errno);
	return (s);
}
