NAME = cub3d
BONUS_NAME = cub3d_bonus
CC = gcc
MLX= mlx/libmlx.a

SRC = main.c ray_casting/init.c ray_casting/draw.c ray_casting/mouvement.c ray_casting/minimap.c ray_casting/rays.c ray_casting/distances.c \
		parcing/get_line.c parcing/pars_utils.c parcing/parcing.c ray_casting/texture.c ray_casting/check_wall.c \
		parcing/parc_utils2.c parcing/parc_utils3.c parcing/parc_utils4.c  ray_casting/init_helper.c ray_casting/distances_util.c ray_casting/draw_util.c \
		parcing/fill_map.c parcing/lst_array.c parcing/sort_path.c parcing/parc_color.c parcing/player.c \
		parcing/check_map.c parcing/valid_map.c 

BONUS_SRC = 

OBJ = $(SRC:.c=.o) 

BONUS_OBJ = $(BONUS_SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address

all: $(NAME)

bonus: $(BONUS_OBJ)
	$(CC) $(BONUS_OBJ) -Lmlx -lmlx -Ofast -framework OpenGL -framework AppKit -o $(BONUS_NAME)


%.o: %.c 

$(MLX):
	make -C mlx/

$(NAME): $(MLX) $(OBJ)
	$(CC) $(OBJ) mlx/libmlx.a -g -fsanitize=address -Lmlx -lmlx -Ofast -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(FLAGS)  -Imlx -c $< -o $@

clean_mlx:
	make clean -C mlx/ 

clean: clean_mlx
	rm -f $(OBJ) $(BONUS_OBJ)

fclean : clean clean_mlx
	@rm -rf $(NAME) $(BONUS_NAME) 

re : fclean all