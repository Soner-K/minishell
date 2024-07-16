NAME				=	minishell


FILES				=	error.c tokenization_utils.c tokenization_utils2.c create_tokens.c path_finding.c \
						utils.c exec_utils.c parsing.c
SRC_DIR				=	src
SRC					=	$(addprefix $(SRC_DIR)/, $(SRC))

LIBFT_PATH			=	libft
LIBFT_EXEC			=	libft.a
LIBFT				=	$(addprefix $(LIBFT_PATH)/, $(LIBFT_EXEC))

OBJ_DIR				=	obj
OBJ					=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror
INCLUDES			=	-I inc -I libft/includes
READLINE			=	-lreadline
DEBUGGER			=	-g3

all					:	$(NAME)

$(LIBFT)			:
						make -s -C libft

$(NAME)				:	$(OBJ_DIR) $(OBJ) $(LIBFT)
						@echo "\n"
						@echo "$(GREEN)Compiling...$(COLOR_END)"
						$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(READLINE) $(DEBUGGER) $(LIBFT) -o $(NAME)
						@echo "$(LGREEN)project compiled !$(COLOR_END)"

$(OBJ_DIR)			:
						mkdir -p $@

$(OBJ_DIR)/%.o		:	$(SRC_DIR)/%.c
						$(CC) $(CFLAGS) $(INCLUDES) $(DEBUGGER) -c $< -o $@
						@printf "$(YELLOW)%s created $(FACE_ESCUZME)$(COLOR_END)\n" $@

clean				:
						rm -rf $(OBJ_DIR)
						make -s -C libft clean

fclean				:	clean
						rm -rf $(NAME)
						rm -rf $(LIBFT)

re					:	fclean all

.PHONY				:	all clean fclean re



LGREEN				=	\033[1;32m
GREEN				=	\033[32m

LBLUE				=	\033[1;34m
BLUE				=	\033[34m

RED					=	\033[31m

LYELLOW				=	\033[1;33m
YELLOW				=	\033[33m

COLOR_END			=	\033[0m

FACE_ESCUZME		=	🤓
BYE					=	🙋
