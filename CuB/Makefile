# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 13:33:36 by mfadil            #+#    #+#              #
#    Updated: 2023/11/09 23:25:18 by mfadil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

FLAGS = -Wall -Wextra -Werror

EXFLAGS = -lmlx -framework OpenGL -framework AppKit

LIBFT = ./libft/libft.a

GNL = Gnl/get_next_line.c Gnl/get_next_line_utils.c

SRC =	cub_hooks.c \
		init.c \
		main.c \
		moving.c \
		raycasting.c \
		render.c \
		utils1.c \
		draw_walls.c \
		parse_map.c \
		parse_utils.c \
		parser.c \
		parser2.c \
		parser3.c \
		parser4.c \
		gc.c \

OBJ_DIR = Objects

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

HEADER = cub3d.h

all: $(NAME)

$(LIBFT):
	make --directory=./libft

$(NAME): $(OBJ) $(LIBFT) $(GNL)
	$(CC) $(FLAGS) $(EXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o:%.c $(HEADER)
	@mkdir -p $(@D) $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make clean --directory=./libft

fclean: clean
	rm -rf $(NAME)
	make fclean --directory=./libft

re: fclean all