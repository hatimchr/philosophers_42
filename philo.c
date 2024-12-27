/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchair <hchair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:17:05 by hchair            #+#    #+#             */
/*   Updated: 2024/12/27 11:03:04 by hchair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_free(t_philo *philo, pthread_mutex_t *forks, pthread_mutex_t *death)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philo)
	{
		pthread_mutex_destroy(philo[i].left_fork);
		pthread_mutex_destroy(philo[i].right_fork);
		i++;
	}
	pthread_mutex_destroy(philo->death);
	pthread_mutex_destroy(forks);
	free(philo->check_dead);
	free(forks);
	free(death);
	free(philo);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*death;

	if (!ft_args_check(ac, av))
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atol(av[1]));
	forks = malloc(sizeof(pthread_mutex_t) * ft_atol(av[1]));
	death = malloc(sizeof(pthread_mutex_t));
	if (!philo || !forks || !death)
		return (1);
	ft_args_init(philo, ac, av);
	ft_mutex_init(philo, forks, death);
	ft_create_threads(philo);
	printf("\n%d",philo->meals_count);
	ft_free(philo, forks, death);
	return (0);
}
