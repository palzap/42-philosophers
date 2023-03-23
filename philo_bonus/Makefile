# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 12:26:28 by pealexan          #+#    #+#              #
#    Updated: 2023/03/23 18:58:44 by pealexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_bonus
HEADER		= philosophers_bonus.h

#----------DIRS----------#

SRC =	actions_bonus.c \
		free_bonus.c \
		init_bonus.c \
		main_bonus.c \
		processes_bonus.c \
		utils_bonus.c \
		utils2_bonus.c \

#--------COMMANDS--------#
CC = clang
CFLAGS = -Wall -Wextra -Werror
EXTRA = -pthread
AR = ar rcs
RM = rm -rf

OBJ = ${SRC:.c=.o}

#---------RULES---------#
.c.o:
			$(CC) $(CFLAGS) -c -I $(HEADER) $< -o ${<:.c=.o}

all: 		$(NAME)

$(NAME): 	$(OBJ) 
			$(CC) $(CFLAGS) $(EXTRA) $(OBJ) -g -o $(NAME)

clean:
			@$(RM) $(OBJ) $(BONUS_OBJ)

fclean: 	clean
			@$(RM) $(NAME)

re: fclean all
