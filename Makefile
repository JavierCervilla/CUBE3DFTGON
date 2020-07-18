# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/10 01:32:21 by dgomez            #+#    #+#              #
#    Updated: 2020/07/18 18:41:39 by jcervill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	Cub3D

INC_DIR			=	./includes/

PRINTF_DIR 		=	$(INC_DIR)printf/

SRC_DIR			=	./src/mandatory/

READ_DIR		=	$(SRC_DIR)read/

RAYCAST_DIR 	=	$(SRC_DIR)raycast/

SRC_DIR_B		=	./src/bonus/

READ_DIR_B		=	$(SRC_DIR_B)read/

RAYCAST_DIR_B 	=	$(SRC_DIR_B)raycast/

MLX_DIR			=	$(INC_DIR)minilibx-linux/

CC				=	gcc

FLAGS			=	-c -Wall -Wextra -Werror

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

bonus: $(NAME)

	@make -C $(PRINTF_DIR)
	@make -C $(MLX_DIR)
	$(CC) $(SRC_DIR_B)*.c $(READ_DIR_B)ft_*.c $(RAYCAST_DIR_B)ft_*.c -lftprintf -L $(PRINTF_DIR) -L$(MLX_DIR) $(MLX_DIR)libmlx.a -lm -lmlx -lXext -lX11 -o  $(NAME)
	@echo "BONUS Done."
	

re: fclean all

.PHONY: all clean fclean