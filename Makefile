# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 17:40:42 by mthamir           #+#    #+#              #
#    Updated: 2025/02/26 16:40:42 by mthamir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minirt

NAME_BONUS := minirt_bonus

CC := cc -Wall -Wextra -Werror

FLAGS :=  -Ofast -I/Users/$(shell whoami)/Desktop/gitminirt/MLX42/include/MLX42

MLX		=	MLX42/libmlx42.a

SHARED_SRC := _Shared_files/basic_operations.c _Shared_files/camera.c \
_Shared_files/colors_operations.c _Shared_files/cylinder_intersection.c \
_Shared_files/cylinder.c _Shared_files/get_first_intersect.c \
_Shared_files/inverse_0.c _Shared_files/inverse_1.c _Shared_files/inverse_2.c \
_Shared_files/matrix_operations_0.c _Shared_files/matrix_operations_1.c \
_Shared_files/parse_char_to.c _Shared_files/parse_error.c \
_Shared_files/parse_get_next_line.c _Shared_files/parse_read_file.c \
_Shared_files/parse_split.c _Shared_files/parse_utils_0.c \
_Shared_files/parse_utils_1.c _Shared_files/plane_intersction.c \
_Shared_files/plane.c _Shared_files/rays_operations.c \
_Shared_files/sphere_intersection.c _Shared_files/sphere.c \
_Shared_files/vectors_operation_2.c _Shared_files/vectors_operations_0.c \
_Shared_files/vectors_operations_1.c

SRC :=  _Mandatory/parse/check_identfier.c _Mandatory/parse/init_lighting.c \
	_Mandatory/parse/init_objects.c _Mandatory/prog_files/lighting.c \
	_Mandatory/prog_files/prepare_computing.c _Mandatory/prog_files/render.c \
	_Mandatory/prog_files/world_intersection.c _Mandatory/parse/init_ambiant_cam.c



SRC_BONUS :=  _Bonus/parse_bonus/check_identfier_bonus.c _Bonus/parse_bonus/init_lighting_bonus.c \
	_Bonus/parse_bonus/init_objects_bonus.c _Bonus/prog_files_bonus/cone_bonus.c \
	_Bonus/prog_files_bonus/cone_intersection_bonus.c _Bonus/prog_files_bonus/lighting_bonus.c \
	_Bonus/prog_files_bonus/prepare_computing_bonus.c _Bonus/prog_files_bonus/render_bonus.c \
	_Bonus/prog_files_bonus/world_intersection_bonus.c _Bonus/parse_bonus/init_ambiant_cam_bonus.c

OBJ_SH := $(SHARED_SRC:.c=.o)

OBJ := $(SRC:.c=.o) $(OBJ_SH)

OBJ_BONUS := $(SRC_BONUS:.c=.o) $(OBJ_SH)

MLXF	=	-framework Cocoa -framework OpenGL -framework IOKit -lglfw -L/Users/$(shell whoami)/.brew/opt/glfw/lib 

HEADER := minirt.h

HEADER_BONUS := minirt_bonus.h

all : $(NAME)

bonus : $(NAME_BONUS)

$(NAME) : $(OBJ) 
	cmake CMakeLists.txt -S MLX42/ -B MLX42/ 
	make -C MlX42
	$(CC) $(FLAGS) $(MLXF) $(OBJ) $(MLX) -o $(NAME)

$(NAME_BONUS) : $(OBJ_BONUS)
	cmake CMakeLists.txt -S MLX42/ -B MLX42/ 
	make -C MlX42
	$(CC) $(FLAGS) $(MLXF) $(OBJ_BONUS) $(MLX) -o $(NAME_BONUS)

%.o : %.c 
	$(CC) $(FLAGS) -c $< -o $@

%bonus.o : %bonus.c $(HEADER_BONUS)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ) $(OBJ_BONUS)

fclean : clean
	make clean -C MLX42/
	rm -f $(NAME) $(NAME_BONUS)

re : fclean all

re_bonus : fclean bonus