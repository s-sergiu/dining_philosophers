
#include "../include/philo.h"

void	custom_time(int ms)
{
	int	i;

	i = 0;
	while (i++ < ms)
		usleep(1000);
}
void	eating(struct s_philos *philo)
{
	int	id;

	id = philo->id;
	pthread_mutex_lock(philo->mutex);
	printf("%d is eating\n", id);
	pthread_mutex_unlock(philo->mutex);
}

void	sleeping(struct s_philos *philo)
{
	int	id;

	id = philo->id;
	pthread_mutex_lock(philo->mutex);
	printf("%d is sleeping\n", id);
	pthread_mutex_unlock(philo->mutex);
}

void	thinking(struct s_philos *philo)
{
	int	id;

	id = philo->id;
	pthread_mutex_lock(philo->mutex);
	printf("%d is thinking\n", id);
	pthread_mutex_unlock(philo->mutex);
}
