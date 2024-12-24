/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchair <hchair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:17:05 by hchair            #+#    #+#             */
/*   Updated: 2024/12/24 15:45:17 by hchair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main(int ac, char **av)
{
    t_table table;
    int i;

    i = 0;
    if (ac < 5 || ac > 6)
        return (printf("invalid argument numbers \n"));
    table.total = ft_atoi(av[1]);
    table.death = (long long)ft_atoi(av[2]);
    table.eat = ft_atoi(av[3]);
    table.sleep = ft_atoi(av[4]);
    if (ac == 6)
        table.meal_limit = ft_atoi(av[5]);
    else
        table.meal_limit = -1;

    if (table.eat < 0 || table.total < 0 || table.sleep < 0 || (ac == 6 && table.meal_limit < 0))
    {
        printf("try something like ./philo 000 000 000 000 [0]\n");
        return(0);
    }

    table.end_simulation = false;
    table.philos = malloc(sizeof(t_philo) * table.total);
    table.forks = malloc(sizeof(t_fork) * table.total);
    if (table.philos == NULL || table.forks == NULL)
        return (0);

    pthread_mutex_init(&table.print_mutex, NULL);

    for (i = 0; i < table.total; i++)
    {
        pthread_mutex_init(&table.forks[i].fork, NULL);
        table.forks[i].fork_id = i;
    }

    for (i = 0; i < table.total; i++)
    {
        table.philos[i].id = i + 1;
        table.philos[i].left_fork = &table.forks[i];
        table.philos[i].right_fork = &table.forks[(i + 1) % table.total];
        table.philos[i].meal_cnt = 0;
        table.philos[i].full = false;
        table.philos[i].thread_id = 0;
        table.philos[i].menu = &table;
        table.philos[i].simulation_start = ft_get_time();
        table.philos[i].last_meal = ft_get_time();
    }

    if (table.total == 1)
    {
        printf("%d has taken a left fork\n", table.philos[0].id);
        usleep(table.death);
        printf("\033[0;31m1 died\033[0m\n");
        return 0;
    }

    for (i = 0; i < table.total; i++)
    {
        if (pthread_create(&table.philos[i].thread_id, NULL, (void *(*)(void *))routine, &table.philos[i]) != 0)
        {
            perror("thread creation failed");
            return (0);
        }
        usleep(100);
    }

    for (i = 0; i < table.total; i++)
    {
        if (pthread_join(table.philos[i].thread_id, NULL) != 0)
        {
            perror("pthread join failed");
            return (1);
        }
    }

    pthread_mutex_destroy(&table.print_mutex);
    for (i = 0; i < table.total; i++)
    {
        pthread_mutex_destroy(&table.forks[i].fork);
    }

    free(table.philos);
    free(table.forks);

    return 0;
}