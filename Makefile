# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/10 01:32:21 by dgomez            #+#    #+#              #
#    Updated: 2020/07/17 02:42:17 by jcervill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

INC_DIR		=	./includes/

PRINTF_DIR 	=	$(INC_DIR)printf/

SRC_DIR		=	./src/

READ_DIR	=	$(SRC_DIR)read/

RAYCAST_DIR =	$(SRC_DIR)raycast/

MLX_DIR		=	$(INC_DIR)minilibx-linux/

CC			=	gcc

FLAGS		=	-c -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@make -C $(PRINTF_DIR)
	@make -C $(MLX_DIR)
	$(CC) $(SRC_DIR)*.c $(READ_DIR)ft_*.c $(RAYCAST_DIR)ft_*.c -lftprintf -L $(PRINTF_DIR)   -L$(MLX_DIR) $(MLX_DIR)libmlx.a -lm -lmlx -lXext -lX11 -o  $(NAME)
	@echo "Done."

debug:
	$(CC) -g $(SRC_DIR)*.c $(READ_DIR)ft_*.c $(RAYCAST_DIR)ft_*.c -lftprintf -L $(PRINTF_DIR)   -L$(MLX_DIR) $(MLX_DIR)libmlx.a -lm -lmlx -lXext -lX11 -o  $(NAME)

compile:
	$(CC) $(SRC_DIR)*.c $(READ_DIR)ft_*.c $(RAYCAST_DIR)ft_*.c -lftprintf -L $(PRINTF_DIR)   -L$(MLX_DIR) $(MLX_DIR)libmlx.a -lm -lmlx -lXext -lX11 -o  $(NAME)

crun: compile
	clear
	@./CUBE3D

clean:
	@make -C $(PRINTF_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "Cleaning Cub3d..."

fclean: clean
	@make -C $(MLX_DIR) clean
	@make -C $(PRINTF_DIR) fclean
	@rm -f $(READ_DIR)*.o
	@rm -f $(RAYCAST_DIR)*.o
	@rm -f $(NAME)
	@echo "Cleaning Cub3d..."

re: fclean all

.PHONY: all clean fclean