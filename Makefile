# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achazal <achazal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 11:54:29 by achazal           #+#    #+#              #
#    Updated: 2014/12/13 12:55:35 by achazal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -------------Compilateur------------------#
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -O3
#--------------Name-------------------------#
NAME = game_2048

#--------------Sources----------------------#
FILES =	main.c			\
		libft.c			\
		utils.c			\
		moves.c

OBJECT = $(patsubst %.c,%.o,$(FILES))
BASEDIR = ./srcs
#-------------------------------------------#



#--------------Actions----------------------#

all:$(NAME)

$(NAME):
		$(CC) -c $(CFLAGS) $(addprefix $(BASEDIR)/, $(FILES))
		$(CC) -o $(NAME) $(OBJECT)
		bash -c "sh setIcon.sh icons/2048_icon.png $(NAME)"
		bash -c "touch auteur && echo \"achazal\" > auteur"
		bash -c "sh setIcon.sh icons/auteur_icon.png auteur"

clean :
		/bin/rm -Rf $(OBJECT)

fclean: clean
		/bin/rm -Rf $(NAME)

re: fclean all
