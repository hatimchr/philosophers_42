/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchair <hchair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:00:01 by hchair            #+#    #+#             */
/*   Updated: 2024/12/24 16:02:48 by hchair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// t_philo	philo;

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

void philo_printer(t_philo *philo, int indx)
{
    if (!pthread_mutex_lock(&philo->menu->print_mutex))
    {
        if (philo->menu->end_simulation)
        {
            pthread_mutex_unlock(&philo->menu->print_mutex);
            return;
        }

        if (indx == 1)
            printf("%lld %d is thinking\n", ft_get_time() - philo->simulation_start, philo->id);
        else if (indx == 2)
            printf("%lld %d is eating\n", ft_get_time() - philo->simulation_start, philo->id);
        else if (indx == 3)
            printf("%lld %d is sleeping\n", ft_get_time() - philo->simulation_start, philo->id);
        else if (indx == 4)
            printf("%lld %d has taken a fork\n", ft_get_time() - philo->simulation_start, philo->id);
        else if (indx == 5)
            printf("%lld %d has reached the meal limit\n", ft_get_time() - philo->simulation_start, philo->id);
        else if (indx == 6)
            printf("\033[0;31m%lld %d died\033[0m\n", ft_get_time() - philo->simulation_start, philo->id);

        pthread_mutex_unlock(&philo->menu->print_mutex);
    }
}
//lme3e9ol
int check_death(t_philo *philo)
{
    if (philo->menu->end_simulation)
        return (0);
    if ((ft_get_time() - philo->last_meal) >= philo->menu->death)
    {
        philo->menu->end_simulation = true;
        philo_printer(philo, 6);
        return (0);
    }
    if ((philo->menu->meal_limit) && philo->meal_cnt == philo->menu->meal_limit)
    {
        philo->menu->end_simulation = true;
        philo_printer(philo, 5);
        return (0);
    }
    return (1);
}

int    ft_philo_wait_time(t_philo *philo, t_time wait_time)
{
    t_time    time;

    time = ft_get_time();
    while (ft_get_time() - time < wait_time)
    {
        if (check_death(philo))
            return (1);
        usleep(100);
    }
    return (0);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (!philo->menu->end_simulation)
    {
        // Philosopher is thinking
        philo_printer(philo, 1);

        // Philosopher is trying to pick up forks
        pthread_mutex_lock(&philo->left_fork->fork);
        philo_printer(philo, 4);
        pthread_mutex_lock(&philo->right_fork->fork);
        philo_printer(philo, 4);

        // Philosopher is eating
        philo_printer(philo, 2);
        philo->meal_cnt++;
        philo->last_meal = ft_get_time();

        // Philosopher is putting down forks
        pthread_mutex_unlock(&philo->right_fork->fork);
        pthread_mutex_unlock(&philo->left_fork->fork);

        // Philosopher is sleeping
        philo_printer(philo, 3);
        ft_philo_wait_time(philo, philo->menu->sleep);

        // Check if philosopher has died
        if (!check_death(philo))
            break;
    }
    return (NULL);
}