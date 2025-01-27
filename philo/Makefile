CC = cc
CFLAGS = -Wall -Wextra -Werror
TEST_CFLAGS = -g

NAME = philo
SRCS =	main.c philosopher.c philosopher_actions.c \
	simulation_prep.c simulation.c clean.c \
	messages.c ph_atoi.c utils.c
SRCS_BONUS =
HEAD = philo.h
OBJS = $(SRCS:.c=.o) $(SRCS_BONUS:.c=.o) $(SRCS_DEBUG)

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
	-./$< 4 300 300 300

norm:
	norminette

ARG1 = 4 600 300 200

test: $(OBJS) $(HEAD)
	$(CC) $(TEST_CFLAGS) -o $(NAME) $(OBJS)

memleak: test
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARG1)
