
#include "../include/philo.h"

void	eating(struct s_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		mutex_lock(philo->left_mutex);
		mutex_lock(&philo->mutex);
		if (is_dead(philo, 0) == FALSE)
			printer_function(philo, 1);
		else 
			return ;
		register_last_meal(&philo);
		philo->fed++;
		ft_sleep(philo->data, philo->data->time_to_eat, philo);
		register_last_meal(&philo);
		mutex_unlock(&philo->mutex);
		mutex_unlock(philo->left_mutex);
	}
	else
	{
		mutex_lock(&philo->mutex);
		mutex_lock(philo->left_mutex);
		if (is_dead(philo, 0) == FALSE)
			printer_function(philo, 1);
		else 
			return ;
		register_last_meal(&philo);
		philo->fed++;
		ft_sleep(philo->data, philo->data->time_to_eat, philo);
		mutex_unlock(philo->left_mutex);
		mutex_unlock(&philo->mutex);
	}
}

void	sleeping(struct s_philos *philo)
{
	printer_function(philo, 2);
	ft_sleep(philo->data, philo->data->time_to_sleep, philo);
}

void	thinking(struct s_philos *philo)
{
	printer_function(philo, 0);
}
