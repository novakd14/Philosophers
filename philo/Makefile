CC = cc
CFLAGS = -Wall -Wextra -Werror
TEST_CFLAGS = -g

NAME = philo
SRCS =	main.c \
		philosopher.c \
		philosopher_actions.c \
		philosopher_actions_utils.c \
		simulation_prep.c \
		simulation.c clean.c \
		messages.c \
		ph_atoi.c \
		utils.c
SRCS_BONUS =
HEAD = philo.h
OBJS = $(SRCS:.c=.o) $(SRCS_BONUS:.c=.o) $(SRCS_DEBUG)

ARG = 3 800 200 200
ARG1 = 4 600 300 200
ARG2 = 3 800 200 200 # timid philosopher dies!!!
ARG3 = 4 800 200 200
ARG4 = 3 400 100 100 1

ARG01 = 1 800 200 200
ARG02 = 5 800 200 200
ARG03 = 5 800 200 200 7
ARG04 = 4 410 200 200
ARG05 = 4 310 200 100
ARG06 = 5 800 200 200

.PHONY: all clean fclean re test norm memleak

all: $(NAME)

$(NAME): $(OBJS) $(HEAD)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME) clean
	-./$< $(ARG06)

norm:
	norminette

test: $(OBJS) $(HEAD)
	$(CC) $(TEST_CFLAGS) -o $(NAME) $(OBJS)

memleak: test
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARG)
