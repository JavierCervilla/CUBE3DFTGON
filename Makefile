# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/10 01:32:21 by dgomez            #+#    #+#              #
#    Updated: 2020/07/17 02:09:50 by jcervill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	CUBE3D

INC_DIR		=	./includes/

PRINTF_DIR 	=	$(INC_DIR)printf/

SRC_DIR		=	./src/

READ_DIR	=	$(SRC_DIR)read/

RAYCAST_DIR =	$(SRC_DIR)raycast/

MLX_DIR		=	$(INC_DIR)minilibx-linux/

CC			=	gcc

FLAGS		=	-c -Wall -Wextra -Werror

SRCS		=	$(addprefix $(SRCS_DIR), $(shell find $(SRCS_DIR)\
					-name "*.c" | rev | cut -d '/' -f1 | rev))

#OBJS_DIR	=	./objects/
#OBJS		=	$(addprefix $(OBJS_DIR), $(shell find $(OBJS_DIR)\
					-name "*.o" | rev | cut -d '/' -f1 | rev))
#OBJECTS		=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

all: $(NAME)

#$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
##	@mkdir -p $(OBJS_DIR)
#	@$(CC) $(FLAGS) -I$(SRCS_DIR) -c $< -o $@

$(NAME): #$(OBJECTS)
	@echo "Adding libft..."
	@make -C $(PRINTF_DIR)
	@make -C $(MLX_DIR)
	@echo "Compiling objects..."
	$(CC)  $(SRC_DIR)*.c $(READ_DIR)ft_*.c $(RAYCAST_DIR)ft_*.c -lftprintf -L $(PRINTF_DIR)   -L$(MLX_DIR) $(MLX_DIR)libmlx.a -lm -lmlx -lXext -lX11 -o  $(NAME)
	#$(CC)  cub3d.c ft_*.c -lftprintf -L $(PRINTF_DIR) -L $(MLX_DIR)libmlx_Linux.a -lmlx   -o  $(NAME)
	@echo "Done."


debug:
	#$(CC) -g cub3d.c ft_*.c -lftprintf -L $(PRINTF_DIR) -L$(MLX_DIR) $(MLX_DIR)libmlx.a -lm -lmlx -lXext -lX11 -o  $(NAME)
	$(CC)  -g $(SRC_DIR)*.c $(READ_DIR)ft_*.c $(RAYCAST_DIR)ft_*.c -lftprintf -L $(PRINTF_DIR)   -L$(MLX_DIR) $(MLX_DIR)libmlx.a -lm -lmlx -lXext -lX11 -o  $(NAME)

compile:
	$(CC)  $(SRC_DIR)*.c $(READ_DIR)ft_*.c $(RAYCAST_DIR)ft_*.c -lftprintf -L $(PRINTF_DIR)   -L$(MLX_DIR) $(MLX_DIR)libmlx.a -lm -lmlx -lXext -lX11 -o  $(NAME)

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
