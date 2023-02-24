
#include "../include/philo.h"

void	eating(struct s_philos *philo)
{
	int	id;

	id = philo->id;
	if (id % 2 == 0)
	{
		mutex_lock(philo->left_mutex);
		if (id == 1)
			printf("\e[1;41;1;41mphilo %d is grabbing %d [left] fork\e[0m\n", id, philo->data->number_of_philos);
		else
			printf("\e[1;41;1;41mphilo %d is grabbing %d [left] fork\e[0m\n", id, id - 1);
		mutex_lock(&philo->mutex);
		printf("\e[1;33mphilo %d is grabbing his [right] fork\e[0m\n", id);
		printf("\e[1;32m %d is eating\e[0m\n", id);
		philo->fed = 1;
		usleep(philo->data->time_to_eat * 1000);
		gettimeofday(&philo->t2, NULL);
		mutex_unlock(philo->left_mutex);
		mutex_unlock(&philo->mutex);
	}
	else
	{
		mutex_lock(&philo->mutex);
		if (id == 1)
			printf("\e[1;41;1;41mphilo %d is grabbing %d [left] fork\e[0m\n", id, philo->data->number_of_philos);
		else
			printf("\e[1;41;1;41mphilo %d is grabbing %d [left] fork\e[0m\n", id, id - 1);
		mutex_lock(philo->left_mutex);
		printf("\e[1;33mphilo %d is grabbing his [right] fork\e[0m\n", id);
		printf("\e[1;32m %d is eating\e[0m\n", id);
		philo->fed = 1;
		usleep(philo->data->time_to_eat * 1000);
		gettimeofday(&philo->t2, NULL);
		mutex_unlock(&philo->mutex);
		mutex_unlock(philo->left_mutex);
	}
}

void	sleeping(struct s_philos *philo)
{
	int	id;

	id = philo->id;
	mutex_lock(&philo->mutex);
	printf("\e[35m %d is sleeping\e[0m\n", id);
	usleep(philo->data->time_to_sleep * 1000);
	gettimeofday(&philo->t2, NULL);
	philo->fed = 0;
	mutex_unlock(&philo->mutex);
}

void	thinking(struct s_philos *philo)
{
	int	id;

	id = philo->id;

	mutex_lock(&philo->mutex);
	printf("\e[1;34m %d is thinking\e[0m\n", id);
	gettimeofday(&philo->t2, NULL);
	mutex_unlock(&philo->mutex);
}
