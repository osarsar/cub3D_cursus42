# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 05:57:52 by stemsama          #+#    #+#              #
#    Updated: 2023/09/14 07:54:20 by stemsama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc

FLAGS = -Wall -Werror -Wextra -fsanitize=address -g
VAR	  = -lmlx -framework OpenGL -framework AppKit

SRC = main.c get_next_line.c get_next_line_utils.c \
		ft_split.c create_map.c create_player.c \
		libft1.c libft2.c\
		tools1.c tools2.c tools3.c tools4.c tools5.c\

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