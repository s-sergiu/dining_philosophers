
#include "../include/philo.h"

void	init_data(struct s_data **data, char **argv)
{
	int	number;

	(*data) = malloc(sizeof(struct s_data));
	(*data)->number_of_philos = atoi_philo(argv[1]);
	(*data)->time_to_die = atoi_philo(argv[2]);
	(*data)->time_to_eat = atoi_philo(argv[3]);
	(*data)->time_to_sleep = atoi_philo(argv[4]);
	(*data)->number_of_eats = 0;
	if (argv[5])
		(*data)->number_of_eats = atoi(argv[5]);
	number = (*data)->number_of_philos;
	(*data)->philosophers = malloc(sizeof(struct s_philos) * number);
	pthread_mutex_init(&(*data)->global_mutex, NULL);
	pthread_mutex_init(&(*data)->routine_mutex, NULL);
	write(1, "Data initialized\n", 17);
}

void	*routine(void *arg)
{
	struct s_philos	*philo;
	long			start;
	long			end;
	long			elapsed;

	philo = arg;
	if (pthread_mutex_lock(&philo->data->global_mutex) != 0)
		printf("Mutex failed to initialize\n");
	if (pthread_mutex_unlock(&philo->data->global_mutex) != 0)
		printf("Mutex failed to initialize\n");
	gettimeofday(&philo->data->t1, NULL);
	while (1)
	{
		eating(philo);
		if (pthread_mutex_lock(&philo->mutex) != 0)
			printf("Mutex failed to initialize\n");
		start = (philo->data->t1.tv_sec * 1000) + (philo->data->t1.tv_usec / 1000);
		end = (philo->t2.tv_sec * 1000) + (philo->t2.tv_usec / 1000);
		elapsed = end - start;
		printf("elapsed %ld\n", elapsed);
		if (pthread_mutex_unlock(&philo->mutex) != 0)
			printf("Mutex failed to initialize\n");
		sleeping(philo);
		thinking(philo);

	}
	printf("routine stopped\n");
	return (NULL);
}

int	numbers_are_incorrect(struct s_data *data)
{
	if (data->number_of_philos == -1)
		return (TRUE);
	if (data->time_to_die < 60)
		return (TRUE);
	if (data->time_to_eat < 60)
		return (TRUE);
	if (data->time_to_sleep < 60)
		return (TRUE);
	if (data->number_of_eats == -1)
		return (TRUE);
	return (FALSE);
}

void	init_philos(struct s_data *data)
{
	int				i;
	struct s_philos	*philos;

	i = -1;
	if (pthread_mutex_lock(&data->global_mutex) != 0)
		printf("Mutex failed to initialize\n");
	philos = data->philosophers;
	print_data(data);
	if (numbers_are_incorrect(data) == TRUE)
	{
		printf("Numbers entered are not correct...\n");
		return ;
	}
	while (++i < data->number_of_philos)
	{
		philos[i].id = i + 1;	
		philos[i].thread = (pthread_t *)malloc(sizeof(pthread_t));	
		pthread_mutex_init(&philos[i].mutex, NULL);
		philos[i].data = data;
		if (i == 0)
		{
			philos[i].left_fork = &data->philosophers[data->number_of_philos - 1].fork;
			philos[i].left_mutex = &data->philosophers[data->number_of_philos - 1].mutex;
		}
		else
		{
			philos[i].left_fork = &data->philosophers[i - 1].fork;
			philos[i].left_mutex = &data->philosophers[i - 1].mutex;
		}
		philos[i].fork = 0;
		philos[i].number = data->number_of_philos;
	}
	i = -1;
	while (++i < data->number_of_philos)
		pthread_create(philos[i].thread, NULL, routine, &philos[i]);
	if (pthread_mutex_unlock(&data->global_mutex) != 0)
		printf("Mutex failed to initialize\n");
	i = -1;
	while (++i < data->number_of_philos)
		pthread_join(*philos[i].thread, NULL);
}
