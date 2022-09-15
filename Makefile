# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 08:30:23 by kaheinz           #+#    #+#              #
#    Updated: 2022/09/15 17:53:40 by kaheinz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c cmd_paths.c tokeniser.c printing.c redirections.c splitter2.c
		

LIBFT = libft/libft.a

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

OS = $(shell uname)
ifeq ($(OS), Linux)
FLAGS_OS = -lreadline 
endif
ifeq ($(OS), Darwin)
FLAGS_OS = -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
endif


$(NAME): $(OBJS)
	make -C libft/
	$(CC) $(CFLAGS) $(FLAGS_OS) -o $(NAME) $(OBJS) $(LIBFT) 

all: $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all 

.PHONY: all clean fclean re

