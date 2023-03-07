
#include "../include/philo.h"

long	get_time(struct s_data *data)
{
	long			current_time;
	long			start_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	mutex_lock(&data->gettime_mutex);
	start_time = (data->t1.tv_sec * 1000) + (data->t1.tv_usec / 1000);
	mutex_unlock(&data->gettime_mutex);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time - start_time);
}

void	*routine(void *arg)
{
	struct s_philos	*philo;

	philo = arg;
	if (philo->left_mutex == NULL)
	{
		printf("%ld\t%d has died\n", get_time(philo->data), philo->id);
		return (NULL);
	}
	mutex_lock(&philo->data->global_mutex);
	mutex_unlock(&philo->data->global_mutex);
	mutex_lock(&philo->data->gettime_mutex);
	gettimeofday(&philo->data->t1, NULL);
	mutex_unlock(&philo->data->gettime_mutex);
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		mutex_lock(&philo->data->routine_mutex);
		if (philo->data->philo_dead == 1)
			break ;
		mutex_unlock(&philo->data->routine_mutex);
		eating(philo);
		if (philo->fed == philo->data->number_of_eats)
			break ;
		mutex_lock(&philo->data->routine_mutex);
		if (philo->data->philo_dead == 1)
			break ;
		mutex_unlock(&philo->data->routine_mutex);
		sleeping(philo);
		mutex_lock(&philo->data->routine_mutex);
		if (philo->data->philo_dead == 1)
			break ;
		mutex_unlock(&philo->data->routine_mutex);
		thinking(philo);
	}
	mutex_unlock(&philo->data->routine_mutex);
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
	if (data->number_of_eats < 0)
		return (TRUE);
	return (FALSE);
}

void	init_philos(struct s_data *data)
{
	int				i;
	struct s_philos	*philos;

	i = -1;
	mutex_lock(&data->global_mutex);
	philos = data->philosophers;
	if (numbers_are_incorrect(data) == TRUE)
	{
		printf("Numbers entered are not correct...\n");
		return ;
	}
	while (++i < data->number_of_philos)
	{
		philos[i].id = i + 1;
		pthread_mutex_init(&philos[i].mutex, NULL);
		pthread_mutex_init(&philos[i].sleep_mutex, NULL);
		pthread_mutex_init(&philos[i].think_mutex, NULL);
		philos[i].data = data;
		philos[i].last_meal = 0;
		philos[i].fed = 0;
		if (i == 0 && data->number_of_philos != 1)
			philos[i].left_mutex = &philos[data->number_of_philos - 1].mutex;
		else if (data->number_of_philos != 1)
			philos[i].left_mutex = &data->philosophers[i - 1].mutex;
		else
			philos[i].left_mutex = NULL;
		philos[i].number = data->number_of_philos;
	}
	i = -1;
	while (++i < data->number_of_philos)
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
	mutex_unlock(&data->global_mutex);
	i = -1;
	while (++i < data->number_of_philos)
		pthread_join(philos[i].thread, NULL);
	while (1)
	{
		i = 0;
		while (++i < data->number_of_philos)
		{
			if (data->number_of_eats && philos[i].fed > 0)
				break ;
			if (is_dead(&philos[i], 1) == TRUE)
				break ;
			if (i == data->number_of_philos - 1)
				i = -1;
		}
		break ;
	}
	return ;
}
