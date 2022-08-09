/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colloct_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:20:50 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/05 17:24:43 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/*
	intialize the outfile tocken
	intialize the Append tocken
*/
t_tocken	*collect_redirect_g(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->c == '>')
		return (lexer_advc_tocken(lexer,
				init_tocken(TOCKEN_DGREAT, ft_strdup(">>"))));
	return (init_tocken(TOCKEN_GREAT, ft_strdup(">")));
}

/*
	intialize the infile tocken
	intialize the HERDOC tocken
*/

t_tocken	*collect_redirect_l(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->c == '<')
		return (lexer_advc_tocken(lexer,
				init_tocken(TOCKEN_HER_DOC, ft_strdup("<<"))));
	return (init_tocken(TOCKEN_LESS, ft_strdup("<")));
}