SRC_LIBFT		=	$(wildcard src/*.c) 
OBJ_LIBFT		=	$(SRC_LIBFT:.c=.o)

SRC_GNL	=	$(wildcard get_next_line/*.c)
OBJ_GNL	=	$(SRC_GNL:.c=.o)

SRC_PRINTF	=	$(wildcard ft_printf/src/*.c)
OBJ_PRINTF	=	$(SRC_PRINTF:.c=.o)

HEADER	=	libft.h

NAME	=	libft.a

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g3

all		:	$(NAME)
			
%.o		:	%.c
			@$(CC) $(CFLAGS) -c $< -o $@

$(NAME)		:	$(OBJ_LIBFT) $(OBJ_GNL) $(OBJ_PRINTF)
			@ar -rc $(NAME) $(OBJ_LIBFT) $(OBJ_GNL) $(OBJ_PRINTF)

clean		:	
			@rm -f $(OBJ_LIBFT) $(OBJ_GNL) $(OBJ_PRINTF) a.out

fclean		:	clean
			@rm -f $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re exec run
