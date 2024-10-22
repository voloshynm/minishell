SRC =   sources/main.c 															\
		sources/lexer.c sources/lexer_utils.c sources/lexer_helper.c 			\
		sources/lexer_args.c sources/lexer_quotes.c					 			\
		sources/parser.c sources/parser_redirection.c sources/parser_path.c		\
		sources/executor.c sources/executor_pipe.c	sources/executor_utils.c	\
		sources/error_handler.c 												\
		sources/signals.c														\
		sources/environment.c 													\
		sources/environment_utils.c sources/environment_utils2.c				\
		sources/builtins/cd.c sources/builtins/pwd.c sources/builtins/export.c 	\
		sources/builtins/echo.c sources/builtins/unset.c sources/builtins/env.c \
		sources/builtins/exit.c													\

OBJS = ${SRC:.c=.o}
OBJS_BONUS = ${SRC:.c=.o}
NAME = minishell
BONUS = minishell_bonus
CC = cc
CFLAGS = -g -Werror -Wextra -Wall
LIBFT_PATH = ./libft
RM = rm -f

# Define colors
DEF_COLOR = \033[0;39m
ORANGE = \033[0;33m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[1;92m
YELLOW = \033[1;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: ${NAME}

${NAME}: ${OBJS}
	${MAKE} -C ${LIBFT_PATH}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} -L${LIBFT_PATH} -lft -lreadline

${BONUS}: ${OBJS_BONUS}
	${MAKE} -C ${LIBFT_PATH}
	${CC} ${CFLAGS} ${OBJS_BONUS} -o ${BONUS} -L${LIBFT_PATH} -lft -lreadline

bonus: ${BONUS}

clean:
	${MAKE} -C ${LIBFT_PATH} clean 
	${RM} ${OBJS} ${OBJS_BONUS}


fclean: clean
	${RM} ${NAME};
	${RM} ${NAME}_bonus;
	${MAKE} -C ${LIBFT_PATH} fclean 

re: fclean all

.PHONY: all clean fclean re