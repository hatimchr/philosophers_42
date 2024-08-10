
#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

/*
./philo 9 600 200 200 [5]
 */

typedef struct s_var
{
	long	total;
	long	eat;
	long	sleep;
	long	think;
	long	death;
	long	meal_limit;
}			t_data;

typedef	struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}		t_fork;

typedef	struct s_phio
{
	long	meal_cnt;
	long	last_meal; // siince when I did not eat 
	bool	full; // meal count match meals limit
	int		id;
	t_fork	*left_fork;
	t_fork	*right_fork;
	pthread_t	thread_id;// aka our philosopher
};


int	ft_atoi(const char *str);
int	ft_printf(const char *src, ...);
int	ft_strlen(char *str);
int	ft_putnbr(int n);
int	ft_putchar(char c);
int	ft_putstr(char *s);

#endif