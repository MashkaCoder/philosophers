NAME = philo_bonus

SRC = philo_bonus.c\
	ft_atoi.c\
	check_and_init_param.c\
	time.c\
	fork.c\

HDRS = philo_bonus.h

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(HDRS)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
