# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 16:52:22 by ahmaidi           #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/08/19 01:49:58 by ahmaidi          ###   ########.fr        #
=======
#    Updated: 2022/08/19 01:36:42 by ahmez-za         ###   ########.fr        #
>>>>>>> 27e51b4e6825f5a2d137ddf256ab74f6e76f5274
#                                                                              #
# **************************************************************************** #

NAME = parser
CC = gcc 
SRCS = parsing/src/lexer/collect_string.c parsing/src/lexer/collect_string_dollar.c parsing/src/lexer/free_it.c \
parsing/src/lexer/ft_strdup_er.c parsing/src/lexer/colloct_redirect.c parsing/src/lexer/get_string_dollar.c \
parsing/src/lexer/get_string_dqoute.c parsing/src/lexer/get_string_sqoute.c parsing/src/lexer/lexer.c \
parsing/src/lexer/tocken.c parsing/src/lexer/ft_error.c parsing/src/main.c parsing/src/lexer/get_simple_chars.c \
parsing/src/lib/ft_calloc.c parsing/src/lib/ft_split.c parsing/src/lib/ft_putchar_fd.c  parsing/src/lib/ft_putstr_fd.c parsing/src/lib/ft_realloc.c parsing/src/lib/ft_strlen.c parsing/src/lib/ft_isalpha.c parsing/src/lib/ft_strdup.c \
parsing/src/lib/ft_strjoin.c parsing/src/lib/ft_strjoin_char.c parsing/src/lib/ft_substr.c parsing/src/lib/ft_memcpy.c parsing/src/lib/ft_bzero.c parsing/src/lib/ft_isalnum.c \
parsing/src/lib/ft_itoa.c parsing/src/parser/ft_realloc_er.c \
parsing/src/parser/parsing_utils.c parsing/src/parser/parsing_utils2.c parsing/src/parser/free_it.c parsing/src/parser/parsing.c parsing/src/visitor.c \
<<<<<<< HEAD
parsing/src/parser/anlyse_here_doc.c parsing/src/parser/check_error.c parsing/src/parser/fill_args.c parsing/execution/execution.c
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
=======
parsing/src/parser/anlyse_here_doc.c parsing/src/parser/check_error.c parsing/execution/execution.c 
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
>>>>>>> 27e51b4e6825f5a2d137ddf256ab74f6e76f5274
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
