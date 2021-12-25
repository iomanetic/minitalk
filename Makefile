# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tyuuki <tyuuki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/25 01:15:27 by tyuuki            #+#    #+#              #
#    Updated: 2021/12/25 01:20:20 by tyuuki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#include $(wildcard *.d)

NAME =		minitalk
N_SERVER =	server
N_CLIENT =	client

SRCS =		functions.c
SERVER = 	server.c
CLIENT =	client.c
HEADER =	minitalk.h
		  
OBJ =		$(patsubst %.c,%.o,$(SRCS))
S_OBJ =		$(patsubst %.c,%.o,$(SERVER))
C_OBJ =		$(patsubst %.c,%.o,$(CLIENT))

CC =		gcc
FLAGS =		-Wall -Wextra -Werror



all: $(NAME)

$(NAME): $(N_SERVER) $(N_CLIENT)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ -MMD

$(N_SERVER): $(S_OBJ) $(OBJ)
	$(CC) -o $(N_SERVER) $(S_OBJ) $(OBJ)

$(N_CLIENT): $(C_OBJ) $(OBJ)
	$(CC) -o $(N_CLIENT) $(C_OBJ) $(OBJ)
	
re: fclean all

clean:
	rm -f $(OBJ) $(C_OBJ) $(S_OBJ) *.d

fclean: clean
	rm -f  $(NAME) $(N_SERVER) $(N_CLIENT)

.PHONY: all clean fclean re

