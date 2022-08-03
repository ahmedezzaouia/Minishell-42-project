/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:23:17 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/02 15:09:52 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "parsing.h"

typedef struct s_lexer
{
	char			c;
	unsigned int	i;
	char			*contents;
}	t_lexer;

t_lexer		*inti_lexer(char *contents);
void		lexer_advance(t_lexer *lexer);
void		lexer_skip_white_spaces(t_lexer *lexer);
t_tocken	*lexer_get_next_tocken(t_lexer *lexer);
t_tocken	*lexer_collect_string(t_lexer *lexer);
t_tocken	*lexer_advc_tocken(t_lexer *lexer, t_tocken *tocken);
char		*lexer_get_char_as_string(t_lexer *lexer);
#endif