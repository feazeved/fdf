# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/10 18:49:50 by feazeved          #+#    #+#              #
#    Updated: 2025/10/09 21:49:07 by feazeved         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
BONUS_NAME = fdf_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -Iincludes -Ilibft/includes
LFLAGS = -lmlx -lXext -lX11 -lm

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRC_DIR = srcs;
BONUS_DIR = srcs_bonus;

SRC = fdf.c ft_split.c get_next_line.c utils.c keys.c line_algorithm.c utils2.c color.c clean.c parsing.c transforms.c xiaolin_algorithm.c utils3.c camera.c xiaolin_utils.c xiaolin_utils2.c
BONUS_SRC = 

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

MLX_DIR = ./minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lbsd
MLX_INCLUDE = -I$(MLX_DIR)
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

all: $(MLX_LIB) $(NAME) $(LIBFT_LIB)

$(LIBFT_LIB): $(LIBFT_DIR)
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_FLAGS) $(MLX_INCLUDE) $(LFLAGS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT_LIB) $(MLX_FLAGS) $(MLX_INCLUDE) $(LFLAGS) -o $(BONUS_NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

$(MLX_LIB):
	git clone https://github.com/42paris/minilibx-linux.git $(MLX_DIR)
	make -C $(MLX_DIR)

$(LIBFT_DIR):
	git clone https://github.com/feazeved/libft.git $(LIBFT_DIR)
