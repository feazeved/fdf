# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/10 18:49:50 by feazeved          #+#    #+#              #
#    Updated: 2025/09/13 15:20:10 by feazeved         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = fdf

SRC = fdf.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ./minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lbsd
MLX_INCLUDE = -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAGS) $(MLX_INCLUDE) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
