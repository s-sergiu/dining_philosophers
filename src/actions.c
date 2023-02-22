
#include "../include/philo.h"

void	eating(struct s_philos *philo)
{
	int	id;

	id = philo->id;
	if (pthread_mutex_lock(philo->left_mutex) != 0)
		printf("mutex error\n");
	printf("philo %d is grabbing %d [left] fork\n", id, id - 1);
	*philo->left_fork = 1;
	if (pthread_mutex_unlock(philo->left_mutex) != 0)
		printf("mutex error\n");
	if (pthread_mutex_lock(&philo->mutex) != 0)
		printf("mutex error\n");
	printf("philo %d is grabbing his [right] fork \n", id);
	philo->fork = 1;
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
