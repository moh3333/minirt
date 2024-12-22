# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 17:40:42 by mthamir           #+#    #+#              #
#    Updated: 2024/12/21 14:03:21 by mthamir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minirt

CC := cc

FLAGS = -W
FLAGS := -Wall -Wextra -Werror -I/Users/$(shell whoami)/Desktop/gitminirt/MLX42/include/MLX42

MLX		=	MLX42/libmlx42.a

SRC := tools.c

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