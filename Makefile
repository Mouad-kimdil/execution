SRC = execute.c Error.c initialize.c split.c libc.c \
	check_access.c child.c
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g
NAME = execute
INC = execute.h
CC = cc
OBJS = $(addprefix obj/, $(SRC:.c=.o))

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

obj/%.o: %.c ${INC}
	@mkdir -p $(dir $@)
	${CC} ${FLAGS} -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: clean
