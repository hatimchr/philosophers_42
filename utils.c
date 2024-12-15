/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchair <hchair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:00:01 by hchair            #+#    #+#             */
/*   Updated: 2024/12/15 15:17:57 by hchair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philo	philo;

int	ft_atoi(const char *str)
{
	int	i;
	int	rst;
	int	mlt;

	i = 0;
	mlt = 1;
	rst = 0;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			mlt = -1;
		i += 1;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		rst = (rst + (str[i] - '0'));
		if (str[i + 1] >= 48 && str[i + 1] <= 57)
			rst = rst * 10;
		else if (str[i + 1] != '\0' && !(str[i + 1] >= 48 && str[i + 1] <= 57))
			return (-2);
		i += 1;
	}
	return (rst * mlt);
}


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int fork_is_avalaible(t_philo *philo) 
{
	if (pthread_mutex_lock(&philo->left_fork->fork) != 0)
    // printf("%d has taken a left fork\n", philo->id);
	return 0;

    if (pthread_mutex_lock(&philo->right_fork->fork) != 0) 
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
        // printf("%d has released a fork\n", philo->id);
        return 0;
    }
	
    return 1;
}

int print_is_avalaible(t_philo *philo) 
{
	if (pthread_mutex_lock(&philo->menu->print_mutex) != 0)
    // printf("%d has taken a left fork\n", philo->id);
		return 0;

    // if (pthread_mutex_lock(&philo->right_fork->fork) != 0) 
	// {
	// 	pthread_mutex_unlock(&philo->left_fork->fork);
    //     // printf("%d has released a fork\n", philo->id);
    //     return 0;
    // }
	
    return 1;
}

void	release_fork(t_philo *philo)
{
	// printf("%d has relased a fork\n", philo->id); 
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	// printf("%d has relased a fork\n", philo->id); 
}

t_time	ft_get_time(void)
{
	struct timeval	tp;
	t_time			time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (time);
}

void	philo_printer(t_philo *philo, int indx)
{
	// while (print_is_avalaible(philo) == 0)
	// {
	// }
	
	if (!pthread_mutex_lock(&philo->menu->print_mutex))
	{
		if (indx == 2)
		{
			/* code */
			printf("\033[0;32m%lld %d is eating for %ld-th time\033[0m\n", ft_get_time() - philo->simulation_start, philo->id, philo->meal_cnt);
			usleep(philo->menu->eat); // eating
		}
		else if (indx == 3)
		{
			/* code */
			printf("\033[0;34m%lld %d is sleeping\033[0m\n", ft_get_time() - philo->simulation_start, philo->id);
			usleep(philo->menu->sleep);
		}
		else if (indx == 4)
		{
			/* code */
			printf("\033[0;33m%lld %d is thinking \033[0;33m\n", ft_get_time() - philo->simulation_start, philo->id);
		}
		else if (indx == 5)
		{
			/* code */
			// pthread_mutex_lock(&philo->menu->print_mutex);
			printf("\033[0;31mend simulation in philo %d\033[0m\n", philo->id);
			return ;
			// pthread_mutex_unlock(&philo->menu->print_mutex);
		}
		else if (indx == 6)
		{
			/* code */
			// pthread_mutex_lock(&philo->menu->print_mutex);
			printf("\033[0;31m philo %d died\033[0m\n", philo->id);
			return ;
			// pthread_mutex_unlock(&philo->menu->print_mutex);
		}
	pthread_mutex_unlock(&philo->menu->print_mutex);
	}
}
//lme3e9ol
int	check_death(t_philo *philo)
{
	usleep(150);
	if (philo->menu->end_simulation)
		return (0);
	if ((ft_get_time() - philo->simulation_start) >= philo->menu->death)
	{
		/* code */
		philo->menu->end_simulation = true;
		philo_printer(philo, 6);
		pthread_mutex_unlock(&philo->menu->print_mutex); 
		return (0);
	}
	if ((philo->menu->meal_limit) 
		&& philo->meal_cnt == philo->menu->meal_limit)
	{
		philo->menu->end_simulation = true;
		philo_printer(philo, 5);
		pthread_mutex_unlock(&philo->menu->print_mutex); 
		return (0);
		// exit (0);
	}
	
	return (1);
}

void *routine(t_philo *philo)
{
	// static int i;
	
	if (philo->id % 2 && check_death(philo))
		philo_printer(philo, 3);
    // I'll be back for you
    while (!philo->menu->end_simulation && check_death(philo))
	{
        // Implement the philosopher's actions here	
		// Pick up the forks
		if (fork_is_avalaible(philo) != 0 && check_death(philo))
		{
			++philo->meal_cnt;
			philo_printer(philo, 2);
			// philo->simulation_start = ft_get_time() - philo->simulation_start;
			release_fork(philo); // Put down the forks
		}
        // Sleep
		if (check_death(philo))
		{
			// printf("\033[0;34m%d is sleeping\033[0m\n", philo->id);
			philo_printer(philo, 3);
		}
		if (check_death(philo))
		{
			// printf("\033[0;34m%d is sleeping\033[0m\n", philo->id);
			philo_printer(philo, 4);
		}
		// verify end simulation
        // Think
			// philo_printer(philo, 4);
    }
    return NULL;
}
