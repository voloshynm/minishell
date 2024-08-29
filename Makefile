SRC =   main.c \
		gc.c \
		parser.c
		
OBJS = ${SRC:.c=.o}
NAME = minishell
CC = cc
CFLAGS = -Werror -Wextra -Wall
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
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME} -L${LIBFT_PATH} -lft -lreadline
	@echo "$(ORANGE)[minishell]:$(DEF_COLOR) exec file $(GREEN) \t=> Created!$(DEF_COLOR)";

libft:
	@if [ ! -d "$(LIBFT_PATH)" ]; then \
        echo "downloading libft..."; \
    	git clone -b libft_original git@github.com:Sergio0227/Libft.git $(LIBFT_PATH) > /dev/null 2>&1; \
	fi
	@${MAKE} all -C ${LIBFT_PATH} > /dev/null 2>&1
	@echo "${GREEN}LIBFT MADE";

.c.o:
	@${CC} -g -c $< -o ${<:.c=.o}


clean:
	@${MAKE} -C ${LIBFT_PATH} clean > /dev/null 2>&1
	@${RM} ${OBJS}
	@echo -n "$(CYAN)[LIBFT]:$(DEF_COLOR) object files$(RED) \t\t => Removed!$(DEF_COLOR)\n"
	@echo -n "$(CYAN)[minishel]:$(DEF_COLOR) object files$(RED) \t => Removed!$(DEF_COLOR)\n"


fclean: clean
	@${RM} ${NAME};
	@${RM} -rf ${LIBFT_PATH}
	@echo -n "$(CYAN)[minishell]:$(DEF_COLOR)  $(RED)    \t => Removed!$(DEF_COLOR)\n"
	@echo -n "$(CYAN)[LIBFT]:$(DEF_COLOR)$(RED)    \t\t => Removed!$(DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re libft