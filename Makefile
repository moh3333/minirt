# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 17:40:42 by mthamir           #+#    #+#              #
#    Updated: 2024/12/12 17:41:23 by mthamir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minirt

CC := cc

FLAGS := -Wall -Wextra -Werror

MLX_FLAGS := -lmlx -framework OpenGL -framework AppKit

SRC := tools.c

OBJ := $(SRC:.c=.o)

HEADER := minirt.h

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(MLX_FLAGS) $(OBJ)  -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all