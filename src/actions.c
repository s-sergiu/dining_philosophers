
#include "../include/philo.h"

void	register_last_meal(struct s_philos **philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	(*philo)->last_meal = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void	check_for_dead(struct s_philos *philo)
{
	struct timeval	time;
	long			current_time;

	gettimeofday(&time, NULL);
	
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (current_time - philo->last_meal > philo->data->time_to_die)
		philo->is_alive = 0;
}

void	eating(struct s_philos *philo)
{
	int	id;

	id = philo->id;
	if (id % 2 == 0)
	{
		mutex_lock(philo->left_mutex);
		mutex_lock(&philo->mutex);
		printer_function(philo, 1);
		register_last_meal(&philo);
		ft_sleep(philo->data, philo->data->time_to_eat);
		mutex_unlock(&philo->mutex);
		mutex_unlock(philo->left_mutex);
	}
	else
	{
		mutex_lock(&philo->mutex);
		mutex_lock(philo->left_mutex);
		printer_function(philo, 1);
		register_last_meal(&philo);
		ft_sleep(philo->data, philo->data->time_to_eat);
		mutex_unlock(philo->left_mutex);
		mutex_unlock(&philo->mutex);
	}
}

void	sleeping(struct s_philos *philo)
{
	mutex_lock(&philo->sleep_mutex);
	printer_function(philo, 2);
	ft_sleep(philo->data, philo->data->time_to_sleep);
	mutex_unlock(&philo->sleep_mutex);
}

void	thinking(struct s_philos *philo)
{
	mutex_lock(&philo->think_mutex);
	printer_function(philo, 0);
	mutex_unlock(&philo->think_mutex);
}
