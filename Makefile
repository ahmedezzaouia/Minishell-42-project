# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 16:52:22 by ahmaidi           #+#    #+#              #
#    Updated: 2022/08/19 04:38:12 by ahmez-za         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = parser
CC = gcc 
SRCS = minishell/parsing/lexer/collect_string.c minishell/parsing/lexer/collect_string_dollar.c minishell/parsing/lexer/free_it.c \
minishell/parsing/lexer/ft_strdup_er.c minishell/parsing/lexer/colloct_redirect.c minishell/parsing/lexer/get_string_dollar.c \
minishell/parsing/lexer/get_string_dqoute.c minishell/parsing/lexer/get_string_sqoute.c minishell/parsing/lexer/lexer.c \
minishell/parsing/lexer/tocken.c minishell/parsing/lexer/ft_error.c minishell/main.c minishell/parsing/lexer/get_simple_chars.c \
minishell/parsing/lib/ft_calloc.c minishell/parsing/lib/ft_split.c minishell/parsing/lib/ft_putchar_fd.c  minishell/parsing/lib/ft_putstr_fd.c minishell/parsing/lib/ft_realloc.c minishell/parsing/lib/ft_strlen.c minishell/parsing/lib/ft_isalpha.c minishell/parsing/lib/ft_strdup.c \
minishell/parsing/lib/ft_strjoin.c minishell/parsing/lib/ft_strjoin_char.c minishell/parsing/lib/ft_substr.c minishell/parsing/lib/ft_memcpy.c minishell/parsing/lib/ft_bzero.c minishell/parsing/lib/ft_isalnum.c \
minishell/parsing/lib/ft_itoa.c minishell/parsing/parser/ft_realloc_er.c \
minishell/parsing/parser/parsing_utils.c minishell/parsing/parser/parsing_utils2.c minishell/parsing/parser/free_it.c minishell/parsing/parser/parsing.c minishell/parsing/visitor.c \
minishell/parsing/parser/anlyse_here_doc.c minishell/parsing/parser/check_error.c minishell/parsing/parser/fill_args.c minishell/execution/execution.c

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -f
READLINE = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib \
			   -I /Users/$(USER)/.brew/opt/readline/include
all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $(READLINE) $(SRCS) -o parser
	@echo "\033[92mExecution file Created\033[0m"
fclean:
	$(RM) $(NAME)
	@echo "\033[91mExecution file deleted\033[0m"
re: fclean all

.PHONY: all fclean re