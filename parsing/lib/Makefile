# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 20:12:24 by ahmaidi           #+#    #+#              #
#    Updated: 2022/08/25 00:37:48 by ahmaidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

FILES = ft_memset \
		ft_bzero \
		ft_memcpy \
		ft_memmove \
		ft_memchr \
		ft_memcmp \
		ft_strlen \
		ft_strlcpy \
		ft_strlcat \
		ft_strchr \
		ft_strrchr \
		ft_strnstr \
		ft_strncmp \
		ft_atoi \
		ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_toupper \
		ft_tolower \
		ft_calloc \
		ft_strdup \
		ft_substr \
		ft_strjoin \
		ft_strtrim \
		ft_split \
		ft_itoa \
		ft_strmapi \
		ft_putchar_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_striteri \
		ft_realloc \
		ft_lstnew_bonus \
	  	ft_lstadd_front_bonus \
	  	ft_lstsize_bonus \
	  	ft_lstlast_bonus \
	  	ft_lstadd_back_bonus \
	  	ft_lstdelone_bonus \
	  	ft_lstclear_bonus \
	  	ft_lstiter_bonus \
	  	ft_lstmap_bonus

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

all: $(NAME)

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c  $(SRCS)
	@echo "\033[92mObjects files created\033[0m"

$(NAME): $(OBJS)
	@$(AR) $@ $^
	@echo "\033[92mLibrary is Created\033[0m"
	@$(RM) $(OBJS)
clean:
	@$(RM) $(OBJS)
	@echo "\033[91mObjects files deleted\033[0m"
fclean: clean
	@$(RM) $(NAME)
	@echo "\033[91mLibrary is deleted\033[0m"
re: clean all

.PHONY: bonus all clean fclean re