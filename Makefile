# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/23 22:58:05 by tlecas            #+#    #+#              #
#    Updated: 2018/04/10 16:00:51 by tlecas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
SRC_PATH = ./srcs/
SRC_NAME = 	main.c \
			rt.c \
			keys.c \
			ft_reflection.c \
			ft_light.c \
			ft_shadow.c \
			ft_prep_shadow.c \
			ft_cone.c \
			ft_plan.c \
			ft_sphere.c \
			ft_init.c \
			ft_img.c \
			ft_tools.c \
			ft_cylinder.c \
			ft_parse.c \
			ft_parse_main_properties.c \
			ft_parse_sphere.c \
			ft_parse_camera.c \
			ft_parse_light.c \
			ft_parse_plane.c \
			ft_parse_cone.c \
			ft_parse_cylinder.c \
			ft_parse_tools.c \
			ft_concat_c_params.c
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ_PATH = ./obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ofast -march=native
CPPFLAGS = -Iincludes -Ilibft/includes -Iminilibx_macos
OPTI_MODE = -g
LIBFT = ./libft/libft.a
MLX = ./minilibx_macos/libmlx.a
FRAMEWORK = -framework OpenGL -framework AppKit

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $^ -o$@ $(FRAMEWORK)

$(LIBFT):
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C minilibx_macos

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	$(MAKE) -C libft MAKEFLAGS= clean

fclean: clean
	rm -fv $(NAME)
	$(MAKE) -C libft MAKEFLAGS= fclean
	$(MAKE) -C minilibx_macos MAKEFLAGS= clean

remove: clean
	rm -fv $(NAME)

clear_screen:
	@clear

extend_cflags:
	$(eval CFLAGS += $(OPTI_MODE))

optimize: | remove extend_cflags $(NAME)
	$(NAME)

re: fclean all
