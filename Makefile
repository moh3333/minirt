# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 17:40:42 by mthamir           #+#    #+#              #
#    Updated: 2025/02/08 13:12:28 by mthamir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minirt

CC := cc

FLAGS :=  -I/Users/$(shell whoami)/Desktop/gitminirt/MLX42/include/MLX42

MLX		=	MLX42/libmlx42.a

SRC :=  _Mandatory/parse/utils_0.c _Mandatory/parse/utils_1.c _Mandatory/parse/char_to.c  \
		_Mandatory/parse/check_identfier.c _Mandatory/parse/error.c _Mandatory/parse/get_next_line.c \
		_Mandatory/parse/init_camera.c _Mandatory/parse/init_lighting.c _Mandatory/parse/init_objects.c \
		_Mandatory/parse/read_file.c _Mandatory/parse/split.c  \
		_Mandatory/prog_files/basic_operations.c _Mandatory/prog_files/camera.c \
		_Mandatory/prog_files/colors_operations.c _Mandatory/prog_files/cylinder.c   _Mandatory/prog_files/cylinder_intersection.c \
		_Mandatory/prog_files/inverse_0.c  _Mandatory/prog_files/inverse_1.c _Mandatory/prog_files/inverse_2.c \
		_Mandatory/prog_files/lighting.c _Mandatory/prog_files/matrix_operations_0.c  \
		_Mandatory/prog_files/matrix_operations_1.c _Mandatory/prog_files/plane.c _Mandatory/prog_files/plane_intersection.c \
		_Mandatory/prog_files/prepare_computing.c _Mandatory/prog_files/rays_operations.c \
		_Mandatory/prog_files/render.c _Mandatory/prog_files/sphere.c _Mandatory/prog_files/sphere_intersection.c \
		_Mandatory/prog_files/vectors_operations_0.c _Mandatory/prog_files/vectors_operations_1.c \
		_Mandatory/prog_files/vectors_operations_2.c _Mandatory/prog_files/world_intersection.c \

OBJ := $(SRC:.c=.o)

MLXF	=	-framework Cocoa -framework OpenGL -framework IOKit -lglfw -L/Users/$(shell whoami)/.brew/opt/glfw/lib 

HEADER := minirt.h

all : $(NAME)

$(NAME) : $(OBJ)
	cmake CMakeLists.txt -S MLX42/ -B MLX42/ 
	make -C MlX42
	$(CC) $(FLAGS) $(MLXF) $(OBJ) $(MLX) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	make clean -C MLX42/
	rm -f $(NAME)

re : fclean all
