/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:15:23 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/21 05:09:20 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <string.h>
# include <errno.h>
# include "../parsing/lib/libft.h"
# include "tocken.h"
# include "lexer.h"
# include <readline/readline.h>
# include <readline/history.h>

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
	int				heredoc[2];
}	t_redir;

typedef struct s_AST
{
	char			**args;
	int				size_args;
	t_redir			**redirec;
	int				size_redirec;
	int				is_builten;
}	t_AST;

typedef struct s_pipes
{
	t_AST	**tab_cmd;
	int		nbre_pipes;
}	t_pipes;

typedef struct s_parser
{
	t_lexer		*lexer;
	t_tocken	*cur_tocken;
	t_tocken	*prev_tocken;
}	t_parser;

/* init the parser */
t_parser		*init_parser(char *cmd);

/* init the Abstract tree */

void			execution(t_pipes *pipes, char **env);
void			ft_cd_cmd(t_AST *pipe_strc);

t_AST			*init_ast(void);
t_pipes			*parser_parse(t_parser *parser);
t_AST			*get_ast_simple_cmd(t_parser *parser);
int				check_syntax_cmd(t_parser *parser);
void			collect_args(t_parser *parser, t_AST *ast);
void			*ft_realloc_er(void *old_alloc, size_t count, size_t old_size);
int				parser_expected(t_parser *parser, t_tocken_type type);
void			free_tocken(t_tocken *tocken);
t_type_redir	get_type_redirect(t_parser *parser);
int				collect_redirect(t_parser *parser, t_AST *ast);
int				visitor(t_pipes *ast);
void			free_tocken(t_tocken *tocken);
void			free_parser(t_parser *parser);
t_AST			*free_ast_cmd(t_AST *ast);
t_pipes			*free_ast_pipe(t_pipes *pipes);
void			alloc_redirec(t_AST *ast);
void			analyse_here_doc(t_parser *parser,
					t_type_redir *type, int index_c);
void			get_ast_pipeline(t_parser *parser, t_pipes **pipes);
void			check_error_max_here_doc(char *cmd_line);
int				check_ambiguous(int status);
void			fill_args(char ***args, char **str, int *size);
int				not_redirect(t_tocken *tocken);
#endif