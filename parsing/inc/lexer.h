/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:23:17 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/17 23:24:59 by ahmaidi          ###   ########.fr       */
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
	int				is_ambg;
	int				exit_status;
}	t_lexer;

t_lexer		*init_lexer(char *contents);
void		lexer_advance(t_lexer *lexer);
void		lexer_skip_white_spaces(t_lexer *lexer);
t_tocken	*lexer_get_next_tocken(t_lexer *lexer);
t_tocken	*lexer_collect_string(t_lexer *lexer);
t_tocken	*lexer_advc_tocken(t_lexer *lexer, t_tocken *tocken);
char		*lexer_get_char_as_string(t_lexer *lexer);
char		*get_value_exit(t_lexer *lexer);
char		*get_env_variable(t_lexer *lexer, int status);
void		lexer_collect_string_dollar(t_lexer *lexer, char **s);
int			diff_of_special_chars(char c);
int			find_closed_qoute(t_lexer *lexer, char c);
t_tocken	*lexer_collect_string(t_lexer *lexer);
t_tocken	*collect_redirect_g(t_lexer *lexer);
t_tocken	*collect_redirect_l(t_lexer *lexer);
void		ft_error(int err);
void		lexer_get_string_dqoute(t_lexer *lexer, char **s);
char		*get_string_dquote(t_lexer *lexer);
char		*get_string_squote(t_lexer *lexer);
char		*get_simple_chars(t_lexer *lexer);
char		*ft_strdup_er(char *str);
char		*get_string_dollar(t_lexer	*lexer);
char		*ft_split_word(char *s);
void		free_it(char **s);
#endif