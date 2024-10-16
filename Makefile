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
NAME = minishell
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

all: libft ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} -L${LIBFT_PATH} -lft -lreadline

libft:
	if [ ! -d "$(LIBFT_PATH)" ]; then \
		echo "downloading libft..."; \
		git clone -b additional_functions git@github.com:Sergio0227/Libft.git $(LIBFT_PATH); \
	fi
	${MAKE} all -C ${LIBFT_PATH}

clean:
	${MAKE} -C ${LIBFT_PATH} clean 
	${RM} ${OBJS}


fclean: clean
	${RM} ${NAME};
	${RM} -rf ${LIBFT_PATH}

re: fclean all

.PHONY: all clean fclean re libft
