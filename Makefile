NAME = philo

SRCS = philosophers.c utils.c utilsph.c table.c main.c

CC = gcc

CFLAGS = -pthread -Wall -Wextra -Werror -g

FLAGS_DATARACE = -fsanitize=thread

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

data_race:
	$(CC) $(FLAGS_DATARACE) $(SRCS) -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
