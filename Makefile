NAME =	philo

SRC =	philo.c \
		sim.c \
		utils.c \
		pthread.c

INCLUDE	= Includes/
FLAGS	= -Wall -Wextra -Werror
CC		= gcc

$(NAME): $(SRC)
	@$(CC) $(FLAGS) -I$(INCLUDE) $(SRC) -o $(NAME)
	@echo "\033[32mPhilosophers are ready!\nUse ./philo 🤔 💀 🍝 💤 🤮 (optional) to start.\n\033[33m🤔 - number of philosophers\n💀 - time to die in milliseconds\n🍝 - time to eat in milliseconds\n💤 - time to sleep in milliseconds\n🤮 - number of times each philosophers must eat"

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)

.PHONY: re
re: fclean all

.PHONY: bonus
bonus: