CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

PHILO = philo
PHILO_BONUS = philo_bonus

MANDATORY = philo.c	utils.c	
CL_OBJ = $(CL_MANDATORY:.c=.o)

SV_BONUS_SRC = server_bonus.c	tool.c	ft_printf.c
SV_BONUS_OBJ = $(SV_BONUS_SRC:.c=.o)

CL_BONUS_SRC = client_bonus.c	ft_printf.c	tool.c
CL_BONUS_OBJ = $(CL_BONUS_SRC:.c=.o)

all: @build

@build: $(PHILO)


%.o:%.c philosopher.h 
	@$(CC) $(CFLAGS) -c $< -o $@

$(SERVER): $(SV_OBJ)
	@$(CC) $(CFLAGS) $(SV_OBJ) -o server
	@echo	"\033[0;32mserver Compiled successeuly\033[0m"
$(CLIENT): $(CL_OBJ)
	@$(CC) $(CFLAGS) $(CL_OBJ) -o client
	@echo	"\033[0;32mclient Compiled successeuly\033[0m"
	
$(SERVER_BONUS): $(SV_BONUS_OBJ) 
	@$(CC) $(CFLAGS) $(SV_BONUS_OBJ) -o server_bonus
	@echo	"\033[0;32mserver bonus Compiled successeuly\033[0m"
$(CLIENT_BONUS): $(CL_BONUS_OBJ)
	@$(CC) $(CFLAGS) $(CL_BONUS_OBJ)	-o client_bonus
	@echo	"\033[0;32mclient bonus Compiled successeuly\033[0m"

clean:
	@echo "\033[0;31mCleaning up...\033[0m"
	@echo "\033[0;31mCleaning up...\033[0m"
	@echo "\033[0;31mCleaning up...\033[0m"
	@$(RM) $(SV_OBJ) $(CL_OBJ)
	@$(RM) $(SV_BONUS_OBJS) $(CL_BONUS_OBJ)
fclean: clean
	@$(RM) $(SERVER) $(CLIENT)
	@$(RM) $(SERVER_BONUS) $(CLIENT_BONUS)
re: fclean all

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)