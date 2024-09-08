/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchair <hchair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:00:01 by hchair            #+#    #+#             */
/*   Updated: 2024/09/08 17:15:28 by hchair           ###   ########.fr       */
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

int	fork_is_avalaible(t_philo philo)
{
	if (pthread_mutex_lock(&philo.left_fork->fork) != 0)
		return (0);
	if (pthread_mutex_lock(&philo.right_fork->fork) != 0)
	{
		pthread_mutex_unlock(&philo.left_fork->fork);
		return (0);
	}
	return (1);
}

void	release_fork(t_philo philo)
{
	pthread_mutex_unlock(&philo.left_fork->fork);
	pthread_mutex_unlock(&philo.right_fork->fork);
}

void *routine()
{
    // I'll be back for you
    while (!philo.menu->end_simulation)
	{
        // Implement the philosopher's actions here
        // Pick up the forks
		if (fork_is_avalaible(philo))
		{
			/* code */
		}
		
        // Eat
        // Put down the forks
        // Sleep
        // Think
    }

    return NULL;
}
