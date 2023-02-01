
#include "../include/philo.h"

void	init_data(struct s_data **data, char **argv)
{
	int	number;

	(*data) = malloc(sizeof(struct s_data));
	(*data)->number_of_philos = atoi(argv[1]);
	(*data)->time_to_die = atoi(argv[2]);
	(*data)->time_to_eat = atoi(argv[3]);
	(*data)->time_to_sleep = atoi(argv[4]);
	(*data)->counter = 0;
	if (argv[5])
		(*data)->number_of_eats = atoi(argv[5]);
	number = (*data)->number_of_philos;
	(*data)->mutex = malloc(sizeof(pthread_mutex_t));
	(*data)->philosophers = malloc(sizeof(struct s_philos*) * number);
	write(1, "Data initialized\n", 17);
}

void	*routine(void *arg)
{
	struct s_philos	*philo;

	philo = arg;
	pthread_mutex_lock(philo->mutex);
	while (*(philo)->counter < 10000)
	{
		*(philo)->counter += 1;
	}
	pthread_mutex_unlock(philo->mutex);
	printf("routine stopped\n");
	return (NULL);
}

void	init_philos(struct s_data *data)
{
	int				i;
	struct s_philos	**philos;

	i = -1;
	philos = data->philosophers;
	while (++i < data->number_of_philos)
	{
		philos[i] = malloc(sizeof(struct s_philos));
		philos[i]->id = i;	
		philos[i]->thread = malloc(sizeof(pthread_t));	
		philos[i]->mutex = data->mutex;	
		philos[i]->counter = &data->counter;	
	}
	i = -1;
	while (++i < data->number_of_philos)
		pthread_create(&philos[i]->thread, NULL, routine, philos[i]);
	i = -1;
	while (++i < data->number_of_philos)
		pthread_join(philos[i]->thread, NULL);
}
