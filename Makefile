# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 08:30:23 by kaheinz           #+#    #+#              #
#    Updated: 2022/09/09 09:31:51 by kaheinz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c

LIBFT = libft/libft.a

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Werror -Wall -Wextra

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

