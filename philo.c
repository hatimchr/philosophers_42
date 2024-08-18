#include "philosopher.h"

int main(int ac, char **av)
{
    t_table table;

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
    // start to fill our info and creat the philosophers
    table.end_simulation = false;
    table.philos = malloc(sizeof(t_philo) * table.total);
    if (table.philos == NULL)
        return (0);
        // initialise philos
    for (int i = 0; i < table.total; i++) 
    {
        table.philos[i].id = i;
        table.philos[i].left_fork = &table.forks[i];
        table.philos[i].right_fork = &table.forks[(i + 1) % table.total];
        // /gettimeofday(&table.philos[i].last_meal, NULL);
        table.philos[i].meal_cnt = 0;
        table.philos[i].full = false;
        table.philos[i].thread_id = 0; // Initialize to 0, not the actual thread ID
        table.philos[i].menu = &table;
    }
}
