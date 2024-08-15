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
    table.philos = malloc(sizeof(table.philos) * table.total);
    if (table.philos == NULL)
        return (0);
    
}
