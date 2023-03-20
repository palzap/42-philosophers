# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 12:26:28 by pealexan          #+#    #+#              #
#    Updated: 2023/03/20 12:25:49 by pealexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
HEADER		= philosophers.h

#----------DIRS----------#

SRC =	main.c \
		destroy.c \
		utils.c \

#--------COMMANDS--------#
CC = clang
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf

OBJ = ${SRC:.c=.o}

#---------RULES---------#
.c.o:
			$(CC) $(CFLAGS) -c -I $(HEADER) $< -o ${<:.c=.o}

all: 		$(NAME)

$(NAME): 	$(OBJ) 
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
			@$(RM) $(OBJ) $(BONUS_OBJ)

fclean: 	clean
			@$(RM) $(NAME)

re: fclean all
