# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmartin- <gmartin-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/08 12:07:39 by gmartin-          #+#    #+#              #
#    Updated: 2020/06/08 13:44:48 by gmartin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	CUBE3D

INC_DIR		=	./includes/

PRINTF_DIR 	=	$(INC_DIR)printf/

#MLX_DIR		=	$(INC_DIR)mlx/
MLX_DIR		=	/home/zalillo/Documentos/cub3d/minilibx  #TODO :tengo referenciada la mlx que tengo fuera
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
	$(CC)  cub3d.c ft_*.c -lftprintf -L $(PRINTF_DIR) -lmlx -L $(MLX_DIR) -o  $(NAME)
	@echo "Done."


debug:
	$(CC) -g cub3d.c ft_*.c -lftprintf -L $(PRINTF_DIR) -lmlx -L $(MLX_DIR) -o  $(NAME)

compile:
	$(CC)  cub3d.c ft_*.c -lftprintf -L $(PRINTF_DIR) -lmlx -L $(MLX_DIR) -o  $(NAME)

crun: compile
	clear
	@./CUBE3D

clean:
	@make -C $(PRINTF_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "Cleaning hashcode objects..."
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make -C $(MLX_DIR) clean
	@make -C $(PRINTF_DIR) fclean
	@rm -f $(NAME)
	@echo "Cleaning Cub3d..."

re: fclean all

.PHONY: all clean fclean