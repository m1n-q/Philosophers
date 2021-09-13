CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = $(wildcard *.c)

OBJS = ${SRCS:.c=.o}

NAME = philo

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lpthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
