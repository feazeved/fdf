# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/10 18:49:50 by feazeved          #+#    #+#              #
#    Updated: 2025/10/12 22:55:45 by feazeved         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
BONUS_NAME = fdf_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -Iincludes -Ilibft/includes -I$(MLX_DIR)
LFLAGS = -lmlx -lXext -lX11 -lm -lbsd

SRC_DIR = srcs
BONUS_DIR = srcs_bonus
OBJ_DIR = objs
LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux

LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

SRC = fdf.c keys.c line_algorithm.c \
	utils2.c color.c clean.c parsing.c \
	transforms.c xiaolin_algorithm.c utils3.c \
	camera.c xiaolin_utils.c xiaolin_utils2.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lbsd
MLX_INCLUDE = -I$(MLX_DIR)

all:$(NAME)


$(NAME): $(LIBFT_LIB) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_FLAGS) $(MLX_INCLUDE) $(LFLAGS) -o $(NAME)


bonus: $(BONUS_NAME)


$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT_LIB) $(MLX_FLAGS) $(MLX_INCLUDE) $(LFLAGS) -o $(BONUS_NAME)


$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
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


clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean


fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	make -C $(LIBFT_DIR) fclean


re: fclean all


.PHONY: all clean fclean re
