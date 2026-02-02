# NAME	:= cub3D

# CC		:= cc
# CFLAGS	:= -Wall -Wextra -Werror -g


# MLX_DIR	:= /Users/maeskhai/Desktop/cub3d-main2/mlx
# MLX_INC	:= $(MLX_DIR)
# MLX_LIB	:= $(MLX_DIR) -lmlx
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
# 			parsing/init_textures.c \
# 			parsing/check_map_errors.c \
# 			parsing/utils/split_rgb2.c \
# 			parsing/init_colors.c \
# 			parsing/check_map_errors2.c \
# 			parsing/check_map_errors3.c \

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

MLX_DIR	:= /home/abdo/curses/cub/cub3d-main5/mlx
MLX_INC	:= -I$(MLX_DIR)
MLX_LIB	:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz


SRC		:=  cub3d.c \
			game/pixel.c \
			game/draw.c \
			game/init_game.c \
			game/free.c \
			game/moves_utils.c \
			game/init_colors_textures.c \
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
			parsing/init_textures.c \
			parsing/check_map_errors.c \
			parsing/utils/split_rgb2.c \
			parsing/init_colors.c \
			parsing/check_map_errors2.c \
			parsing/check_map_errors3.c \


OBJ		:= $(SRC:.c=.o)
HEADER	:= parsing/cub3d.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) -o $(NAME)

%.o: %.c $(HEADER) /maps/*.cub
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
