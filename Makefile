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

CC = cc

NAME = fdf

SRC = fdf.c ft_split.c get_next_line.c utils.c keys.c line_algorithm.c utils2.c color.c clean.c parsing.c transforms.c xiaolin_algorithm.c utils3.c camera.c xiaolin_utils.c xiaolin_utils2.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -O3 -g

LFLAGS = -lmlx -lXext -lX11 -lm

MLX_DIR = ./minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lbsd
MLX_INCLUDE = -I$(MLX_DIR)
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAGS) $(MLX_INCLUDE) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(MLX_LIB):
	git clone https://github.com/42paris/minilibx-linux.git $(MLX_DIR)
	make -C $(MLX_DIR)

