NAME = cub3d
BONUS_NAME = cub3d_bonus
CC = gcc

SRC = main.c

BONUS_SRC = 

OBJ = $(SRC:.c=.o) 

BONUS_OBJ = $(BONUS_SRC:.c=.o) 

all: $(NAME)

bonus: $(BONUS_OBJ)
	$(CC) $(BONUS_OBJ) -Lmlx -lmlx -Ofast -framework OpenGL -framework AppKit -o $(BONUS_NAME)


%.o: %.c 

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -Ofast -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c cub3d.h
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean : clean
	@rm -rf $(NAME) $(BONUS_NAME)

re : fclean all