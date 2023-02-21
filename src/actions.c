
#include "../include/philo.h"

void	eating(struct s_philos *philo)
{
	int	id;
	int	number;

	pthread_mutex_lock(&philo->mutex);
	id = philo->id;
	number = philo->number;
	if (id == 1)
	{
		printf("philo %d is grabbing %d [left] fork\n", id, number);
		philo->data->philosophers[number - 1].fork = 1;
	}
	else 
	{
		printf("philo %d is grabbing %d [left] fork\n", id, id - 1);
		philo->data->philosophers[id - 1].fork = 1;
	}
	printf("philo %d is grabbing his [right] fork \n", id);
	philo->fork = 1;
	printf("%d is eating\n", id);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->mutex);
}

void	sleeping(struct s_philos *philo)
{
	int	id;

	id = philo->id;
	pthread_mutex_lock(&philo->mutex);
	printf("%d is sleeping\n", id);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->mutex);
}

void	thinking(struct s_philos *philo)
{
	int	id;

	id = philo->id;
	pthread_mutex_lock(&philo->mutex);
	printf("%d is thinking\n", id);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->mutex);
}
