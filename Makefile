NAME = cub3d
BONUS_NAME = cub3d_bonus
CC = gcc

SRC = main.c init.c draw.c mouvement.c minimap.c rays.c distances.c texture.c

BONUS_SRC = 

OBJ = $(SRC:.c=.o) 

BONUS_OBJ = $(BONUS_SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address

all: $(NAME)

bonus: $(BONUS_OBJ)
	$(CC) $(BONUS_OBJ) -Lmlx -lmlx -Ofast -framework OpenGL -framework AppKit -o $(BONUS_NAME)


%.o: %.c 

$(NAME): $(OBJ)
	$(CC) $(OBJ) mlx/libmlx.a -g -fsanitize=address -Lmlx -lmlx -Ofast -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(FLAGS)  -Imlx -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean : clean
	@rm -rf $(NAME) $(BONUS_NAME)

re : fclean all