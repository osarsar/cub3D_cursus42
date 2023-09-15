SRCS = 	main.c	\
		get_next_line.c	\
		get_next_line_utils.c	\
		ft_split.c		\
		create_map.c	\
		create_player.c	\

NAME = cub3D.a

FLAGS = -Wall -Werror -Wextra #-g -fsanitize=address

%.o : %.c cub3D.h
	@echo "Compiling: $<"
	@cc $(FLAGS) -c $< -o $@

$(NAME) : $(SRCS:.c=.o)
	@ar -r $(NAME) $(SRCS:.c=.o)
	@cc $(FLAGS)  -lmlx -framework OpenGL -framework AppKit $(NAME) -o cub3D

all : $(NAME)

clean :
	@rm -rf $(SRCS:.c=.o)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf cub3D

re : fclean all