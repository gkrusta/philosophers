# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/24 13:15:24 by gkrusta           #+#    #+#              #
#    Updated: 2023/12/10 16:00:37 by gkrusta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
FLAGS = -Wall -Wextra -Werror

HEADERS = -I./inc

SRCS = src/main.c src/routine.c src/philo_init.c src/philo_utils.c src/death_checker.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS)
	@ echo "\033[32mCompiling Philosophers...\n"
	@$(CC) $(FLAGS) $(OBJS) $(HEADERS) -o $@
	@ echo "\n\t\t\033[32mCompiled!\n"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@ $(HEADERS)

RM = rm -f

clean:
	@ $(RM) $(OBJS)
	@ echo "\n\t\t\033[32mEverything is clean!\n"

fclean: clean
	@ $(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
