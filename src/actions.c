
#include "../include/philo.h"

void	eating(struct s_philos *philo)
{
	int	id;
	int	number;

	id = philo->id;
	number = philo->number;
	if (pthread_mutex_lock(&philo->mutex) != 0)
		printf("mutex error\n");
	printf("philo %d is grabbing %d [left] fork\n", id, id - 1);
	(void)philo->left_fork;
	printf("philo %d is grabbing his [right] fork \n", id);
	(void)philo->fork;
	printf("%d is eating\n", id);
	if (pthread_mutex_unlock(&philo->mutex) != 0)
		printf("mutex error\n");
	usleep(philo->data->time_to_eat * 1000);
}

void	sleeping(struct s_philos *philo)
{
	int	id;

	pthread_mutex_lock(&philo->mutex);
	id = philo->id;
	printf("%d is sleeping\n", id);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->mutex);
}

void	thinking(struct s_philos *philo)
{
	int	id;

	pthread_mutex_lock(&philo->mutex);
	id = philo->id;
	printf("%d is thinking\n", id);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->mutex);
}
