#include "philosopher.h"

int main(int ac, char **av)
{
    t_data philo;

    if (ac < 5 || ac > 6)
        return (printf("invalid argument numbers \n"));
    philo.total = ft_atoi(av[1]);
    philo.death = ft_atoi(av[2]);
    philo.eat = ft_atoi(av[3]);
    philo.sleep = ft_atoi(av[4]);
    
}
