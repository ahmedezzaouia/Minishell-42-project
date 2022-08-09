# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 16:52:22 by ahmaidi           #+#    #+#              #
#    Updated: 2022/08/08 13:07:42 by ahmaidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parser
CC = gcc 
SRCS = parsing/src/lexer/collect_string.c parsing/src/lexer/collect_string_dollar.c parsing/src/lexer/free_it.c \
parsing/src/lexer/ft_strdup_er.c parsing/src/lexer/colloct_redirect.c parsing/src/lexer/get_string_dollar.c \
parsing/src/lexer/get_string_dqoute.c parsing/src/lexer/get_string_sqoute.c parsing/src/lexer/lexer.c \
parsing/src/lexer/tocken.c parsing/src/lexer/ft_error.c parsing/src/main.c parsing/src/lexer/get_simple_chars.c \
parsing/src/lib/ft_calloc.c parsing/src/lib/ft_split.c parsing/src/lib/ft_strlen.c parsing/src/lib/ft_isalpha.c parsing/src/lib/ft_strdup.c \
parsing/src/lib/ft_strjoin.c parsing/src/lib/ft_strjoin_char.c  parsing/src/lib/ft_substr.c parsing/src/lib/ft_bzero.c parsing/src/lib/ft_isalnum.c \
parsing/src/lib/ft_itoa.c parsing/src/get_next_line/get_next_line_utils.c parsing/src/get_next_line/get_next_line.c
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
RM = rm -f
all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o parser
	@echo "\033[92mExecution file Created\033[0m"
fclean:
	$(RM) $(NAME)
	@echo "\033[91mExecution file deleted\033[0m"
re: fclean all

.PHONY: all fclean re