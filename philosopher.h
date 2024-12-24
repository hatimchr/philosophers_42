/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchair <hchair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:17:12 by hchair            #+#    #+#             */
/*   Updated: 2024/12/24 12:51:09 by hchair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

typedef unsigned long long	t_time;

typedef struct s_var		t_table;

typedef	struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}		t_fork;

typedef	struct s_phio
{
	long			meal_cnt;
	t_time			last_meal; // siince when I did not eat 
	t_time			simulation_start;
	bool			full; // meal count match meals limit
	int				id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;// aka our philosopher number
	t_table			*menu;
}				t_philo;

struct s_var
{
	pthread_mutex_t	print_mutex;		
	long			total;
	long			eat;
	long			sleep;
	long			think;
	t_time			death;
	long			meal_limit;
	bool			end_simulation; // a philo died or all of them are full
	t_philo			*philos; // array of people who talk a lot
	t_fork			*forks; // array of forks 
};

int		ft_atoi(const char *str);
int		ft_printf(const char *src, ...);
int		ft_strlen(char *str);
int		ft_putnbr(int n);
int		ft_putchar(char c);
int		ft_putstr(char *s);
void	*routine();
t_time	ft_get_time(void);
int    ft_philo_wait_time(t_philo *philo, t_time wait_time);

#endif