/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_string_dollar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:40:57 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/04 22:26:20 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/*
	retrun the value of exist status
*/

char	*get_value_exit(t_lexer *lexer)
{
	(void)lexer;
	printf("exit\n");
	return (NULL);
}

/*
	search in env Variable 
*/

char	*get_env_variable(t_lexer *lexer)
{
	char	*s;
	int		start;
	int		end;
	char	*tmp;

	start = lexer->i;
	while (ft_isalnum(lexer->c) || lexer->c == '_')
		lexer_advance(lexer);
	end = lexer->i;
	s = ft_substr(lexer->contents, start, end - start);
	if (s == NULL)
		ft_error(errno);
	tmp = s;
	s = getenv(s);
	if (!s)
		s = ft_strdup("");
	free(tmp);
	return (s);
}

/*
	expand the string next to  $ with three cases :
	1) $_ || ${isalpha} search in env variables
	2) the opposit of case 1
	3) $? the exit status
	 
*/

void	lexer_collect_string_dollar(t_lexer *lexer, char **s)
{
	char	*tmp;

	tmp = NULL;
	lexer_advance(lexer);
	if (lexer->c == '?')
		tmp = get_value_exit(lexer);
	else if (lexer->c != '_' && !ft_isalpha(lexer->c))
	{
		*s = ft_strjoin_char(*s, lexer->c);
		if (*s)
			ft_error(errno);
		lexer_advance(lexer);
	}
	else
		tmp = get_env_variable(lexer);
	*s = ft_strjoin(*s, tmp, 1);
	if (*s == NULL)
		ft_error(errno);
}
