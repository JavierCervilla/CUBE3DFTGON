NAME	=	libftprintf.a

SRCS	=	ft_printf.c \
			ft_check.c \
			ft_printf_hexa.c \
			ft_printf_integer.c \
			ft_printf_string.c \
			ft_printf_utils.c \
			ft_printf_utils2.c 

OBJS	:= ${SRCS:.c=.o}

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I.
RM		= rm -f

all:	${NAME}

%.o: %.c
		${CC} ${CFLAGS} -c $< -o $@
%.o: libft/%.c
	${CC} ${CFLAGS} -c $< -o $@
${NAME}:${OBJS}
		make -C libft
		ar rc ${NAME} libft/*.o ${OBJS}
debug:
		$(CC) $(CFLAGS) -g $(SRCS) libft/ft_*.c -I libft

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME} libft/*.o *.o

re:		fclean all
.PHONY: all clean fclean re
