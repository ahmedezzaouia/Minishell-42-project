/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:15:23 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/09 18:19:21 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <string.h>
# include <errno.h>
# include "../src/lib/libft.h"
# include "../src/get_next_line/get_next_line.h"
# include "tocken.h"
# include "lexer.h"

int	g_exit_status;

typedef enum s_type_redir
{
	INPUT,
	OUTPUT,
	APPAND,
	HERE_DOC
}	t_type_redir;

typedef struct s_redir
{
	t_type_redir	type;
	char			*filename;
}	t_redir;
typedef enum s_type_cmd
{
	SIMPLE_CMD,
	PIPELINE,
}	t_type_cmd;

typedef struct s_AST
{
	t_type_cmd		type;
	struct s_AST	*pipe;
	int				pipe_size;
	char			**args;
	int				size_args;
	t_redir			**redirec;
	int				size_redirec;
}	t_AST;

typedef struct s_parser
{
	t_lexer		*lexer;
	t_tocken	*cur_tocken;
	t_tocken	*prev_tocken;
}	t_parser;

/* init the parser */
t_parser		*init_parser(char *cmd, int exit_status);

/* init the Abstract tree */

t_AST			*init_ast(t_type_cmd type);
t_AST			*parser_parse(t_parser *parser);
t_AST			*get_ast_simple_cmd(t_parser *parser);
int				check_syntax_cmd(t_parser *parser);
void			collect_args(t_parser *parser, t_AST *ast);
void			*ft_realloc_er(void *ptr, size_t size, size_t oldsize);
int				parser_expected(t_parser *parser, t_tocken_type type);
void			free_tocken(t_tocken *tocken);
t_type_redir	get_type_redirect(t_parser *parser);
int				collect_redirect(t_parser *parser, t_AST *ast);

#endif