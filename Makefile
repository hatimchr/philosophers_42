CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread  -fsanitize=address
RM = rm -rf

PHILO = philo
PHILO_BONUS = philo_bonus

MANDATORY = philo.c utils.c
PL_OBJ = $(MANDATORY:.c=.o)

all: $(PHILO)

%.o: %.c philosopher.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(PHILO): $(PL_OBJ)
	@$(CC) $(CFLAGS) $(PL_OBJ) -o $(PHILO)
	@echo "\033[0;32mphilo Compiled successfully\033[0m"

clean:
	@echo "\033[0;31mCleaning up...\033[0m"
	@$(RM) $(PL_OBJ)

fclean: clean
	@$(RM) $(PHILO)

re: fclean all