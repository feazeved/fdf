# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/10 18:49:50 by feazeved          #+#    #+#              #
#    Updated: 2025/10/07 19:37:49 by feazeved         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = fdf

SRC = fdf.c ft_split.c get_next_line.c utils.c keys.c line_algorithm.c utils2.c color.c clean.c parsing.c transforms.c xiaolin_algorithm.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g -O3

LFLAGS = -lmlx -lXext -lX11 -lm

MLX_DIR = ./minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lbsd
MLX_INCLUDE = -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAGS) $(MLX_INCLUDE) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
