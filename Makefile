# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 17:40:42 by mthamir           #+#    #+#              #
#    Updated: 2025/01/13 19:15:35 by mthamir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minirt

CC := cc

FLAGS :=  -fsanitize=address -Wall -Wextra -Werror -I/Users/$(shell whoami)/Desktop/gitminirt/MLX42/include/MLX42
#FLAGS := -lmlx -framework OpenGL -framework AppKit


MLX		=	MLX42/libmlx42.a

SRC := tools/ft_malloc.c tools/light_0.c tools/math_0.c tools/math_1.c tools/matrix_0.c tools/matrix_1.c \
	tools/matrix_2.c tools/matrix_3.c tools/matrix_4.c tools/reflection_0.c tools/sphere_0.c tools/sphere_1.c \
	tools/tuples_0.c tools/tuples_1.c tools/tuples_2.c tools/colors.c tools/intersection.c main.c

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

# NAME := minirt

# CC := cc

# FLAGS := -Wall -Wextra -Werror

# MLX_FLAGS := -lmlx -framework OpenGL -framework AppKit

# SRC := tools.c

# OBJ := $(SRC:.c=.o)

# HEADER := minirt.h

# all : $(NAME)

# $(NAME) : $(OBJ)
# 	$(CC) $(FLAGS) $(MLX_FLAGS) $(OBJ)  -o $(NAME)

# %.o : %.c $(HEADER)
# 	$(CC) $(FLAGS) -c $< -o $@

# clean :
# 	rm -f $(OBJ)

# fclean : clean
# 	rm -f $(NAME)

# re : fclean all