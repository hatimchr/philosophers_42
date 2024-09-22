/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchair <hchair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:17:05 by hchair            #+#    #+#             */
/*   Updated: 2024/09/22 21:17:06 by hchair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main(int ac, char **av)
{
    t_table table;
    int i;

    i = 0;
    // Parsing argument and passe it to table struct || I'll creat a function later
    if (ac < 5 || ac > 6)
        return (printf("invalid argument numbers \n"));
    table.total = ft_atoi(av[1]);
    table.death = ft_atoi(av[2]);
    table.eat = ft_atoi(av[3]);
    table.sleep = ft_atoi(av[4]);
    if (ac == 6)
    table.meal_limit = ft_atoi(av[5]);

    if (table.death < 0 || table.eat < 0
        || table.total < 0 || table.sleep < 0
        || table.meal_limit < 0) 
        {
            printf("try somthing like./philo 000 000 000 000 [0]\n");
            exit (0);
        }
    // start to fill  info and creat the philosophers
    table.end_simulation = false;
    table.philos = malloc(sizeof(t_philo) * table.total);
    if (table.philos == NULL)
        return (0);
        // initialise philos
    for (i = 0; i < table.total; i++) 
    {
        table.philos[i].id = i + 1;
        table.philos[i].left_fork = &table.forks[i];
        table.philos[i].right_fork = &table.forks[(i + 1) % table.total];
        // /gettimeofday(&table.philos[i].last_meal, NULL);
        table.philos[i].meal_cnt = 0;
        table.philos[i].full = false;
        table.philos[i].thread_id = 0; // Initialize to 0, not the actual thread ID
        table.philos[i].menu = &table;
    }
    // initialise forks
    table.forks = malloc(sizeof(t_fork) * table.total);
    if (table.forks == NULL)
        return 0;
    for (i = 0; i < table.total; i++) {
        pthread_mutex_init(&table.forks[i].fork, NULL);
        table.forks[i].fork_id = i;
        table.philos[i].left_fork = &table.forks[i];
        table.philos[i].right_fork = &table.forks[(i + 1) % table.total];
    }
    // creat threads
    i = 0;
    while (i <  table.total)
    {
        if (pthread_create(&table.philos[i].thread_id, NULL, &routine, &table.philos[i]) != 0)
        {
            perror("thread creation failed");
            return (0);
        }
        i++;
    }
    for ( i = 0; i < table.total; i++)
    {
         if (pthread_join(table.philos[i].thread_id, NULL) != 0)
        {
            perror("pthread join failed");
            return (1);
        }
    }
}
