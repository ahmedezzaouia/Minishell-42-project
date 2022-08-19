# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 16:52:22 by ahmaidi           #+#    #+#              #
#    Updated: 2022/08/19 15:58:02 by ahmaidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = gcc 
SRCS = parsing/lexer/collect_string.c \
parsing/lexer/collect_string_dollar.c \
parsing/lexer/free_it.c \
parsing/lexer/ft_strdup_er.c \
parsing/lexer/colloct_redirect.c \
parsing/lexer/get_string_dollar.c \
parsing/lexer/get_string_dqoute.c \
parsing/lexer/get_string_sqoute.c \
parsing/lexer/lexer.c \
parsing/lexer/tocken.c \
parsing/lexer/ft_error.c \
main.c \
parsing/lexer/get_simple_chars.c \
parsing/lib/ft_calloc.c \
parsing/lib/ft_split.c \
parsing/lib/ft_putchar_fd.c \
parsing/lib/ft_putstr_fd.c \
parsing/lib/ft_realloc.c \
parsing/lib/ft_strlen.c \
parsing/lib/ft_isalpha.c \
parsing/lib/ft_strdup.c \
parsing/lib/ft_strjoin.c \
parsing/lib/ft_strjoin_char.c \
parsing/lib/ft_substr.c \
parsing/lib/ft_memcpy.c \
parsing/lib/ft_bzero.c \
parsing/lib/ft_isalnum.c \
parsing/lib/ft_itoa.c \
parsing/parser/ft_realloc_er.c \
parsing/parser/parsing_utils.c \
parsing/parser/parsing_utils2.c \
parsing/parser/free_it.c \
parsing/parser/parsing.c \
parsing/visitor.c \
parsing/parser/anlyse_here_doc.c \
parsing/parser/check_error.c \
parsing/parser/fill_args.c \
execution/execution.c

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -f
READLINE = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib \
			   -I /Users/$(USER)/.brew/opt/readline/include
all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $(READLINE) $(SRCS) -o $(NAME)
	@echo "\033[92mExecution file Created\033[0m"
fclean:
	$(RM) $(NAME)
	@echo "\033[91mExecution file deleted\033[0m"
re: fclean all

.PHONY: all fclean re