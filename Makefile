# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 05:17:54 by stemsama          #+#    #+#              #
#    Updated: 2023/09/23 23:03:22 by stemsama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D
CC = cc

FLAGS = -Wall -Werror -Wextra -Ofast
VAR	  = -lmlx -framework OpenGL -framework AppKit

SRC = main.c get_next_line.c get_next_line_utils.c \
		libft1.c libft2.c libft3.c \
		tools1.c tools2.c tools3.c tools4.c tools5.c\
		create_map.c create_player.c player_view.c	view.c raycast.c\
		textures.c \
		norm_1.c norm_2.c norm_3.c \

OBJECT = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECT) cub3D.h
	@$(CC) $(FLAGS)  $(OBJECT) -o $(NAME) $(VAR)

%.o:%.c cub3D.h
	@echo "Compiling: $<"
	@$(CC) $(FLAGS) -c $< -o $@

clean :
	@rm -f $(OBJECT)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: clean fclean re all