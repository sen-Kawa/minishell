# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 08:30:23 by kaheinz           #+#    #+#              #
#    Updated: 2022/09/09 10:25:36 by ksura            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c

LIBFT = libft/libft.a

OBJS = $(SRCS:.c=.o)

CC = gcc

OS = $(shell uname)
ifeq ($(OS), Linux)
	CFLAGS = -Werror -Wall -Wextra -lreadline 
endif
ifeq ($(OS), Darwin)
	CFLAGS = -Wall -Werror -Wextra -g -I $(HOME)/goinfre/.brew/opt/readline/include/
endif

$(NAME): $(OBJS)
	make -C libft/
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) 

all: $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all 

.PHONY: all clean fclean re

