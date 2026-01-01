# NAME	:= cub3D

# CC		:= cc
# CFLAGS	:= -Wall -Wextra -Werror -g


# MLX_DIR	:= /home/abdo/MY_CUB3D/cub_ray3/mlx
# MLX_INC	:= -I$(MLX_DIR)
# MLX_LIB	:= -L$(MLX_DIR) -lmlx
# MLX_FW	:= -framework OpenGL -framework AppKit


# SRC		:=  cub3d.c \
# 			game/pixel.c \
# 			game/draw.c \
# 			game/init_game.c \
# 			game/game_utils.c \
# 			game/moves.c \
# 			parsing/parsing.c \
# 			parsing/check_file_name.c \
# 			parsing/print_error.c \
# 			parsing/read_fd.c \
# 			parsing/get_next_line/get_next_line_utils.c \
# 			parsing/get_next_line/get_next_line.c \
# 			parsing/utils/split_rgb.c \
# 			parsing/utils.c \
# 			parsing/check_line.c \
# 			parsing/utils/strtrim.c \
# 			parsing/check_map.c \
# 			parsing/utils/atoi_rgb.c \
# 			parsing/utils/split.c \
# 			parsing/textures_colors.c \
# 			parsing/check_map_errors.c

# OBJ		:= $(SRC:.c=.o)
# HEADER	:= parsing/cub3d.h


# all: $(NAME)

# $(NAME): $(OBJ)
# 	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(MLX_FW) -o $(NAME)

# %.o: %.c $(HEADER)
# 	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

# clean:
# 	rm -rf $(OBJ)

# fclean: clean
# 	rm -rf $(NAME)

# re: fclean all

# .PHONY: all clean fclean re




# for linux mlx

NAME	:= cub3D

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -g

MLX_DIR	:= /home/abdo/MY_CUB3D/cub_ray3/mlx
MLX_INC	:= -I$(MLX_DIR)
MLX_LIB	:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRC		:= cub3d.c \
			game/pixel.c \
			game/draw.c \
			game/init_game.c \
			game/game_utils.c \
			game/moves.c \
			parsing/parsing.c \
			parsing/check_file_name.c \
			parsing/print_error.c \
			parsing/read_fd.c \
			parsing/get_next_line/get_next_line_utils.c \
			parsing/get_next_line/get_next_line.c \
			parsing/utils/split_rgb.c \
			parsing/utils.c \
			parsing/check_line.c \
			parsing/utils/strtrim.c \
			parsing/check_map.c \
			parsing/utils/atoi_rgb.c \
			parsing/utils/split.c \
			parsing/textures_colors.c \
			parsing/check_map_errors.c

OBJ		:= $(SRC:.c=.o)
HEADER	:= parsing/cub3d.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		--suppressions=valgrind_suppress.supp ./$(NAME) maps/map.cub

valgrind-verbose: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		--log-file=valgrind.log ./$(NAME) maps/map.cub

.PHONY: all clean fclean re valgrind valgrind-verbose
