/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchair <hchair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:29:54 by hchair            #+#    #+#             */
/*   Updated: 2024/12/27 11:13:11 by hchair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philo)
	{
		pthread_create(&philo[i].thread, NULL, &philo_routine, &philo[i]);
		i++;
		usleep(100);
	}
	if (ft_check_death(philo))
		return ;
	i = 0;
	while (i < philo->number_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->number_of_philo == 1 && !ft_check_death(philo))
	{
		if (pthread_mutex_lock(philo->left_fork))
			return (NULL);
		ft_philo_print(philo, " has taken a fork", 0);
		while (!ft_check_death(philo))
		{
		}
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		while (1)
		{
			if (ft_check_death(philo))
				break ;
			ft_philo_eat(philo);
			ft_philo_sleep(philo);
			ft_philo_think(philo);
		}
	}
	return (NULL);
}

int	ft_check_death(t_philo *philo)
{
	if (philo->meals_count == philo->must_eat)
		return (1);
	pthread_mutex_lock(philo->death);
	if (*philo->check_dead)
	{
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	pthread_mutex_unlock(philo->death);
	if (ft_get_time() - philo->last_meal > \
		philo->time_to_die)
	{
		ft_philo_print(philo, "died", 1);
		return (1);
	}
	return (0);
}
