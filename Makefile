# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 16:52:22 by ahmaidi           #+#    #+#              #
#    Updated: 2022/08/28 10:46:57 by ahmez-za         ###   ########.fr        #
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
parsing/lexer/env_list.c \
parsing/lexer/get_env.c \
main.c \
parsing/lexer/get_simple_chars.c \
parsing/parser/ft_realloc_er.c \
parsing/parser/parsing_utils.c \
parsing/parser/parsing_utils2.c \
parsing/parser/free_it.c \
parsing/parser/parsing.c \
parsing/visitor.c \
parsing/parser/not_redirect.c \
parsing/parser/anlyse_here_doc.c \
parsing/parser/check_error.c \
parsing/parser/fill_args.c \
execution/execution.c \
execution/ft_cd_cmd.c \
execution/ft_pwd_cmd.c \
execution/ft_echo.c \
execution/ft_env_cmd.c \
execution/redirections.c \
execution/ft_exit.c \
execution/ft_export.c \
execution/ft_display_export.c \
execution/filling_args_export.c \
execution/ft_max_long_exit.c\
execution/ft_herdoc.c \
execution/ft_unset.c\
execution/delete_env.c \
execution/signals.c \
execution/execution_simple_command.c \
execution/execution_multiple_commands.c

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -f
READLINE = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib \
			   -I /Users/$(USER)/.brew/opt/readline/include
LIBFT = ./parsing/lib/libft.a
all: $(NAME)

$(NAME): $(SRCS)
	@make -C ./parsing/lib
	@$(CC) $(CFLAGS) $(READLINE) $(SRCS) $(LIBFT) -o $(NAME)
	@echo "\033[92mExecution file Created\033[0m"

clean:
	@make -C ./parsing/lib clean

fclean:
	@make -C ./parsing/lib fclean
	$(RM) $(NAME)
	@echo "\033[91mExecution file deleted\033[0m"
re: fclean all

.PHONY: all fclean re
