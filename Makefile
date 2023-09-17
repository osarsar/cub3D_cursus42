# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+         #
#                              w
NAME = cub3D
CC = cc

FLAGS = -Wall -Werror -Wextra -fsanitize=address -g
VAR	  = -lmlx -framework OpenGL -framework AppKit

SRC = main.c get_next_line.c get_next_line_utils.c \
		libft1.c libft2.c libft3.c \
		tools1.c tools2.c tools3.c tools4.c tools5.c\
		create_map.c create_player.c player_view.c	\

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