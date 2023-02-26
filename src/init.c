
#include "../include/philo.h"

void	mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
		printf("Mutex failed to initialize\n");
}

void	mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
		printf("Mutex failed to initialize\n");
}

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

void	*watch_dead(void *arg)
{
	struct s_watcher	*watcher;

	watcher = arg;
	while (1)
	{
		sleep(100);
		printf("watcher\n");
	}
	return (NULL);
}

void	ft_sleep(struct s_data *data, int ms)
{
	long			initial_time;

	//get current time;
	initial_time = get_time(data);
	while (get_time(data) - initial_time < ms)
		usleep(200);
}

long	get_time(struct s_data *data)
{
	long			current_time;
	long			start_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	start_time = (data->t1.tv_sec * 1000) + (data->t1.tv_usec / 1000);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time - start_time);

}

void	*routine(void *arg)
{
	struct s_philos	*philo;

	philo = arg;
	mutex_lock(&philo->data->global_mutex);
	mutex_unlock(&philo->data->global_mutex);
	gettimeofday(&philo->data->t1, NULL);
	while (1)
	{
		eating(philo);
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
		philos[i].fed = 0;
		philos[i].number = data->number_of_philos;
	}
	i = -1;
	while (++i < data->number_of_philos)
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
	pthread_create(&data->watcher.thread, NULL, watch_dead, &data->watcher);
	pthread_detach(data->watcher.thread);
	if (pthread_mutex_unlock(&data->global_mutex) != 0)
		printf("Mutex failed to initialize\n");
	i = -1;
	while (++i < data->number_of_philos)
		pthread_join(philos[i].thread, NULL);
}
