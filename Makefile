NAME	:= cub3D

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -g


MLX_DIR	:= mlx
MLX_INC	:= -I$(MLX_DIR)
MLX_LIB	:= -L$(MLX_DIR) -lmlx
MLX_FW	:= -framework OpenGL -framework AppKit


SRC		:= cub3d.c \
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
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(MLX_FW) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	rm -rf $(OBJ)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
