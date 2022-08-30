/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anlyse_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 18:19:18 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/30 04:27:23 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static void	skip_white_spaces(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
}

static void	collect_string_quotes_herdoc(t_parser *parser, char **value, int *i)
{
	char	*str;
	char	c;
	int		start;
	int		ends;

	c = parser->lexer->contents[*i];
	(*i)++;
	start = (*i);
	while (diff_of_special_chars(parser->lexer->contents[*i])
		&& parser->lexer->contents[*i] != c)
		(*i)++;
	ends = (*i);
	str = ft_substr(parser->lexer->contents, start, ends - start);
	if (!str)
		ft_error(errno);
	*value = ft_strjoin(*value, str);
	free(str);
	if (!value)
		ft_error(errno);
}

static void	collect_string_herdoc(t_parser *parser, char **value, int *index_c)
{
	char	*str;
	int		start;
	int		ends;

	start = (*index_c);
	while (diff_of_special_chars(parser->lexer->contents[*index_c])
		&& parser->lexer->contents[*index_c] != '\''
		&& parser->lexer->contents[*index_c] != '"')
		(*index_c)++;
	ends = (*index_c);
	str = ft_substr(parser->lexer->contents, start, ends - start);
	if (!str)
		ft_error(errno);
	*value = ft_strjoin(*value, str);
	free(str);
	if (!value)
		ft_error(errno);
}

void	analyse_here_doc(t_parser *parser, t_type_redir *type, int index_c)
{
	char	*value;

	value = ft_strdup_er("");
	(void) type;
	skip_white_spaces(parser->lexer->contents, &index_c);
	while (diff_of_special_chars(parser->lexer->contents[index_c]))
	{
		if (parser->lexer->contents[index_c] == '\''
			|| parser->lexer->contents[index_c] == '"')
		{
			g_data.is_quotes = 1;
			collect_string_quotes_herdoc(parser, &value, &index_c);
		}
		else
		{
			g_data.is_quotes = 0;
			collect_string_herdoc(parser, &value, &index_c);
		}
	}
	free(parser->prev_tocken->value);
	parser->prev_tocken->value = value;
}
