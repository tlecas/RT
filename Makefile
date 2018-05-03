# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/23 22:58:05 by tlecas            #+#    #+#              #
#    Updated: 2018/05/02 15:30:32 by tlecas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
SRC_PATH = ./srcs/
SRC_NAME = 	main.c \
			rt.c \
			keys.c \
			keys2.c \
			ft_reflection.c \
			ft_light.c \
			ft_shadow.c \
			ft_prep_shadow.c \
			ft_cone.c \
			ft_plane.c \
			ft_sphere.c \
			ft_para.c \
			ft_init.c \
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
			ft_parse_para.c \
			ft_parse_init_obj.c \
			ft_concat_c_params.c \
			ft_rgb_add.c \
			ft_rgbmult.c \
			display_hud.c \
			screenshot.c \
			ft_error.c \
			ft_is_shadow.c \
			ft_black_filter.c \
			ft_sepia_filter.c \
			ft_cartoon_filter.c \
			ft_check_filters.c
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ_PATH = ./obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ofast -march=native
CPPFLAGS = -Iincludes -Ilibft/includes -Iminilibx_macos -Ilodepng
OPTI_MODE = -g
LIBFT = ./libft/libft.a
MLX = ./minilibx_macos/libmlx.a
IMAGES = ./lodepng/lodepng.c
FRAMEWORK = -framework OpenGL -framework AppKit

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX) $(IMAGES)
	$(CC) $(CFLAGS) $^ -o$@ $(FRAMEWORK)

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
