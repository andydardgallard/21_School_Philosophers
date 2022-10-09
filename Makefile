NAME = philo

SRC = main.c parser.c simulation.c utils.c utils2.c

OBJ = $(SRC:.c=.o)

CC = gcc -Wall -Wextra -Werror

all: $(NAME)

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME): $(OBJ)
	@echo "\nCompiling --->"
	@$(CC) -o $@  $^
	@echo "Done\n"

clean:
	@rm -rf $(OBJ)
	@echo "\nDelete objects\n"

fclean: clean
	@rm -rf $(NAME)
	@echo "\nDelete all\n"

re: fclean all
