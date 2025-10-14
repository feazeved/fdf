# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/10 18:49:50 by feazeved          #+#    #+#              #
#    Updated: 2025/10/13 14:51:54 by feazeved         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = fdf
BONUS_NAME = fdf_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -Iincludes -Ilibft -I$(MLX_DIR) -g
LFLAGS = -lmlx -lXext -lX11 -lm -lbsd

SRC_DIR = srcs
OBJ_DIR = objs
BONUS_DIR = srcs_bonus
BONUS_OBJ_DIR = objs_bonus

LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux

LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

SRC = fdf.c keys.c line_algorithm.c \
	utils.c color.c clean.c parsing.c \
	transforms.c  utils2.c \
	camera.c  changes.c mlx_utils.c

BONUS_SRC = fdf_bonus.c keys_bonus.c line_algorithm_bonus.c \
	utils_bonus.c color_bonus.c clean_bonus.c parsing_bonus.c \
	transforms_bonus.c xiaolin_algorithm_bonus.c utils2_bonus.c \
	camera_bonus.c xiaolin_utils_bonus.c xiaolin_utils2_bonus.c menus_bonus.c changes_bonus.c mlx_utils_bonus.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR)/, $(BONUS_SRC:.c=.o))

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lbsd
MLX_INCLUDE = -I$(MLX_DIR)


all: $(NAME)


$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_FLAGS) -lm -o $(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	make -C $(MLX_DIR)


$(LIBFT_LIB):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		git clone https://github.com/feazeved/libft.git $(LIBFT_DIR); \
	fi
	make -C $(LIBFT_DIR)


bonus: $(BONUS_NAME)


$(BONUS_OBJ_DIR):
	mkdir -p $(BONUS_OBJ_DIR)


$(BONUS_NAME): $(LIBFT_LIB) $(MLX_LIB) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT_LIB) $(MLX_FLAGS) -lm -o $(BONUS_NAME)


$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c | $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
