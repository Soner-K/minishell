NAME				=	minishell

SRC_DIR				=	src
OBJ_DIR				=	obj
OBJ_DIRS			=	$(OBJ_DIR)/expand $(OBJ_DIR)/parsing $(OBJ_DIR)/utils $(OBJ_DIR)/builtin \
						$(OBJ_DIR)/env $(OBJ_DIR)/pipe $(OBJ_DIR)/prompt $(OBJ_DIR)/signal \

SRC_FILES			=	expand/expand_utils.c expand/expand.c expand/quotes.c \
						parsing/create_tokens.c parsing/syntax_checker.c parsing/get_cmd_array.c \
						parsing/tokenization_utils.c parsing/tokenization_utils2.c \
						utils/builtins.c utils/error.c utils/path_finding.c utils/utils.c \
						main.c builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c \
						parsing/redirections_setting.c parsing/debugging.c parsing/prep_exec.c parsing/prep_exec_utils.c \
						builtin/export_utils.c builtin/export.c builtin/find_builtin.c \
						builtin/pwd.c builtin/unset.c env/env_utils.c \
						prompt/create_prompt.c signal/init_signal.c pipe/exec_utils.c \
						pipe/runtime.c pipe/heredoc.c pipe/pipe_init.c pipe/pipe_utils.c pipe/redirect_init.c \
						parsing/ft_parse.c 
SRC					=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

LIBFT_PATH			=	libft
LIBFT_EXEC			=	libft.a
LIBFT				=	$(addprefix $(LIBFT_PATH)/, $(LIBFT_EXEC))

OBJ					=	$(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

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

$(OBJ_DIRS)			:
						mkdir -p $(OBJ_DIRS)

$(OBJ_DIR)/%.o		:	$(SRC_DIR)/%.c | $(OBJ_DIRS)
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
