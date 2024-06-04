SRC			=	src/ft_printf.c src/convert.c

SRC_LIBFT	=	../src/ft_putchar_fd.c ../src/ft_putstr_fd.c ../src/ft_strlen.c

HEADER		=	includes/ft_printf.h

OBJ			=	$(SRC:.c=.o)

OBJ_LIBFT	=	$(SRC_LIBFT:.c=.o)

NAME		=	libftprintf.a

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror

EXEC	=	exec

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			make -C ../
			cp ../libft.a $(NAME)
			ar -q $(NAME) $(OBJ)
			
%.o		:	%.c
			$(CC) $(CFLAGS) -c $< -o $@

clean			:	
			rm -f $(OBJ) ../src/*.o ../src/*.gch $(EXEC)

fclean		:	clean
			rm -f $(NAME) ../libft.a

re		:	fclean all

$(EXEC)		:	$(OBJ) $(OBJ_LIBFT)
				@$(CC) $(CFLAGS) $^ -o $@

run			:	$(EXEC)
				@./$(EXEC)

.PHONY		:	all clean fclean re run exec
