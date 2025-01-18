CC = cc
CFLAGS = -Wall -Wextra -Werror
TEST_CFLAGS = -g

NAME = philo
SRCS = main.c ph_atoi.c
SRCS_BONUS =
HEAD = philo.h
OBJS = $(SRCS:.c=.o) $(SRCS_BONUS:.c=.o)

.PHONY: all clean fclean re test norm memleak

all: $(NAME)

$(NAME): $(OBJS) $(HEAD)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME) clean
	-./$< 1 2 3 4

norm:
	norminette

memleak: $(NAME)
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$< $(ARG1) $(ARG2) $(ARG3)
