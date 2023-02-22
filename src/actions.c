
#include "../include/philo.h"

void	eating(struct s_philos *philo)
{
	int	id;

	id = philo->id;
	if (pthread_mutex_lock(philo->left_mutex) != 0)
		printf("Mutex failed to initialize\n");
	printf("\e[1;41;1;41mphilo %d is grabbing %d [left] fork\e[0m\n", id, id - 1);
	if (pthread_mutex_lock(&philo->mutex) != 0)
		printf("Mutex failed to initialize\n");
	printf("\e[1;33mphilo %d is grabbing his [right] fork\e[0m\n", id);
	printf("\e[1;32m %d is eating\e[0m\n", id);
	usleep(philo->data->time_to_eat * 1000);
	gettimeofday(&philo->t2, NULL);
	if (pthread_mutex_unlock(philo->left_mutex) != 0)
		printf("Mutex failed to initialize\n");
	if (pthread_mutex_unlock(&philo->mutex) != 0)
		printf("Mutex failed to initialize\n");
}

void	sleeping(struct s_philos *philo)
{
	int	id;

	id = philo->id;
	pthread_mutex_lock(&philo->mutex);
	printf("\e[35m %d is sleeping\e[0m\n", id);
	usleep(philo->data->time_to_sleep * 1000);
	pthread_mutex_unlock(&philo->mutex);
}

void	thinking(struct s_philos *philo)
{
	int	id;

	id = philo->id;
	pthread_mutex_lock(&philo->mutex);
	printf("\e[1;34m %d is thinking\e[0m\n", id);
	pthread_mutex_unlock(&philo->mutex);
}
