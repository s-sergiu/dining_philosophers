
#include "../include/philo.h"

void	eating(struct s_philos *philo)
{
	int	id;

	id = philo->id;
	if (id % 2 == 0)
	{
		mutex_lock(philo->left_mutex);
		mutex_lock(&philo->mutex);
		printer_function(philo, 1);
		ft_sleep(philo->data, philo->data->time_to_eat);
		mutex_unlock(&philo->mutex);
		mutex_unlock(philo->left_mutex);
	}
	else
	{
		mutex_lock(&philo->mutex);
		mutex_lock(philo->left_mutex);
		printer_function(philo, 1);
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
