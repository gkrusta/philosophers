# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/24 13:15:24 by gkrusta           #+#    #+#              #
#    Updated: 2023/12/01 15:18:06 by gkrusta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BONUS = philo_bonus

CC = gcc
FLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=thread

HEADERS = -I./inc_bonus

SRCS_BONUS = src_bonus/main.c src_bonus/routine.c src_bonus/philo_init.c \
			src_bonus/philo_utils.c src_bonus/death_checker.c

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@ echo "\033[32mCompiling Philosophers bonus...\n"
	@$(CC) $(FLAGS) $(OBJS_BONUS) $(HEADERS) -o $@
	@ echo "\n\t\t\033[32mCompiled!\n"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@ $(HEADERS)

RM = rm -f

clean:
	@ $(RM) $(OBJS) $(OBJS_BONUS)
	@ echo "\n\t\t\033[32mEverything is clean!\n"

fclean: clean
	@ $(RM) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
