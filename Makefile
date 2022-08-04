# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 16:52:22 by ahmaidi           #+#    #+#              #
#    Updated: 2022/08/04 17:29:29 by ahmaidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parser
CC = gcc 
SRCS = parsing/src/lexer/collect_string.c parsing/src/lexer/collect_string_dollar.c parsing/src/lexer/colloct_redirect.c parsing/src/lexer/get_string_dollar.c parsing/src/lexer/get_string_dqoute.c parsing/src/lexer/get_string_sqoute.c parsing/src/lexer/lexer.c parsing/src/lexer/tocken.c parsing/src/lexer/ft_error.c \
parsing/src/lib/ft_calloc.c parsing/src/lib/ft_strlen.c parsing/src/lib/ft_isalpha.c parsing/src/lib/ft_strdup.c parsing/src/lib/ft_strjoin.c parsing/src/lib/ft_strjoin_char.c  parsing/src/lib/ft_substr.c parsing/src/lib/ft_bzero.c parsing/src/lib/ft_isalnum.c
CFLAGS = -Wall -Wextra -Werror 
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