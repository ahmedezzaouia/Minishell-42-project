/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_string_dollar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:40:57 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/16 17:19:57 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/* remove multiple spaces */

char	*ft_split_word(char *s)
{
	char	**tmp;
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup_er("");
	tmp = ft_split(s, ' ');
	if (!tmp)
		ft_error(errno);
	while (tmp[i])
	{
		str = ft_strjoin(str, tmp[i]);
		if (!str)
			ft_error(errno);
		if (tmp[i + 1])
		{
			str = ft_strjoin(str, " ");
			if (!str)
				ft_error(errno);
		}
		i++;
	}
	free_it(tmp);
	return (str);
}

/*
	retrun the value of exist status
*/

char	*get_value_exit(t_lexer *lexer)
{
	char	*s;

	s = ft_itoa(lexer->exit_status);
	if (s == NULL)
		ft_error(errno);
	lexer_advance(lexer);
	return (s);
}

/*
	search in env Variable 
*/

char	*get_env_variable(t_lexer *lexer, int status)
{
	char	*s;
	int		start;
	int		end;
	char	*tmp;

	(void)status;
	start = lexer->i;
	while (ft_isalnum(lexer->c) || lexer->c == '_')
		lexer_advance(lexer);
	end = lexer->i;
	s = ft_substr(lexer->contents, start, end - start);
	if (s == NULL)
		ft_error(errno);
	tmp = s;
	s = getenv(s);
	free(tmp);
	if (!s)
	{
		s = ft_strdup_er("");
		lexer->is_ambg = 1;
	}
	else if (status == 1)
		s = ft_split_word(s);
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
	char	*str;

	lexer_advance(lexer);
	if (lexer->c == '?')
		str = get_value_exit(lexer);
	else if (lexer->c != '_' && !ft_isalpha(lexer->c))
	{
		str = ft_substr(lexer->contents, lexer->i - 1, 2);
		if (!str)
			ft_error(errno);
		lexer_advance(lexer);
	}
	else
		str = get_env_variable(lexer, 0);
	*s = ft_strjoin(*s, str);
	if (ft_strlen(str) == 0)
		free(str);
	if (*s == NULL)
		ft_error(errno);
}
