
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
	long end;
	long elapsed;

	gettimeofday(&philo->t2, NULL);
	id = philo->id;
	end = philo->data->t1.tv_usec / 1000 + philo->data->t1.tv_sec;
	elapsed = (philo->t2.tv_usec / 1000 + philo->t2.tv_sec) - end;
	printf("time elapsed is %ld\n", elapsed);
	printf("time elapsed is %ld\n", elapsed);
	pthread_mutex_lock(philo->mutex);
	printf("%d is eating\n", id);
	pthread_mutex_unlock(philo->mutex);
	custom_time(philo->data->time_to_eat);
}

void	sleeping(struct s_philos *philo)
{
	int	id;
	long end;
	long elapsed;

	gettimeofday(&philo->t2, NULL);
	id = philo->id;
	end = philo->data->t1.tv_usec / 1000 + philo->data->t1.tv_sec;
	elapsed = (philo->t2.tv_usec / 1000 + philo->t2.tv_sec) - end;
	printf("time elapsed is %ld\n", elapsed);
	pthread_mutex_lock(philo->mutex);
	printf("%d is sleeping\n", id);
	pthread_mutex_unlock(philo->mutex);
	custom_time(philo->data->time_to_eat);
}

void	thinking(struct s_philos *philo)
{
	int	id;
	long end;
	long elapsed;

	gettimeofday(&philo->t2, NULL);
	id = philo->id;
	end = philo->data->t1.tv_usec / 1000 + philo->data->t1.tv_sec;
	elapsed = (philo->t2.tv_usec / 1000 + philo->t2.tv_sec) - end;
	printf("time elapsed is %ld\n", elapsed);
	pthread_mutex_lock(philo->mutex);
	printf("%d is thinking\n", id);
	pthread_mutex_unlock(philo->mutex);
	custom_time(philo->data->time_to_eat);
}
