CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDES = -I includes/
SRC = src/main.c src/handle_args.c src/time.c src/prep_dining.c src/routine.c src/utils.c src/actions.c src/cleanup.c
OBJ = $(SRC:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
