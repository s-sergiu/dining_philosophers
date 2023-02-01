
#include "../include/philo.h"

void	init_data(struct s_data **data, char **argv)
{
	int	number;

	(*data) = malloc(sizeof(struct s_data));
	(*data)->number_of_philos = atoi(argv[1]);
	(*data)->time_to_die = atoi(argv[2]);
	(*data)->time_to_eat = atoi(argv[3]);
	(*data)->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		(*data)->number_of_eats = atoi(argv[5]);
	write(1, "Data initialized\n", 17);
	number = (*data)->number_of_philos;
	(*data)->philosophers = malloc(sizeof(struct s_philos*) * number);
}

void	*routine(void *arg)
{
	struct s_philos	*philo;

	philo = arg;

	while (1)
	{
		printf("id is %d\n", philo->id);
		sleep(2);
	}
	return (NULL);
}

void	init_philos(struct s_data *data)
{
	int				i;
	struct s_philos	**philos;

	i = 0;
	philos = data->philosophers;
	while (i < data->number_of_philos)
	{
		philos[i] = malloc(sizeof(struct s_philos));
		philos[i]->id = i;	
		philos[i]->thread = malloc(sizeof(pthread_t));	
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_create(&philos[i]->thread, NULL, routine, philos[i]);
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
}
