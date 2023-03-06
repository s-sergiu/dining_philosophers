
#include "../include/philo.h"

void	register_last_meal(struct s_philos **philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	(*philo)->last_meal = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

int	is_dead(struct s_philos *philo)
{
	struct timeval	time;
	long			current_time;

	
	if (philo->is_alive == 0)
		return (TRUE);
	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (philo->last_meal == 0)
	{
		current_time = get_time(philo->data);
		if (current_time == philo->data->time_to_die)
		{
			philo->is_alive = 0;
			mutex_lock(&philo->data->routine_mutex);
			philo->data->philo_dead = 1;
			mutex_unlock(&philo->data->routine_mutex);
			printf("%ld\t%d has died\n", get_time(philo->data), philo->id);
			return (TRUE);
		}
	}
	if (current_time - philo->last_meal >= philo->data->time_to_die)
	{
		philo->is_alive = 0;
		mutex_lock(&philo->data->routine_mutex);
		philo->data->philo_dead = 1;
		mutex_unlock(&philo->data->routine_mutex);
		printf("%ld\t%d has died\n", get_time(philo->data), philo->id);
		return (TRUE);
	}
	return (FALSE);
}

void	eating(struct s_philos *philo)
{
	int	id;

	id = philo->id;
	if (id % 2 == 0)
	{
		mutex_lock(philo->left_mutex);
		mutex_lock(&philo->mutex);
		if (philo->is_alive == 1)
			printer_function(philo, 1);
		else
			return ;
		register_last_meal(&philo);
		ft_sleep(philo->data, philo->data->time_to_eat, philo);
		mutex_unlock(&philo->mutex);
		mutex_unlock(philo->left_mutex);
	}
	else
	{
		mutex_lock(&philo->mutex);
		mutex_lock(philo->left_mutex);
		if (philo->is_alive == 1)
			printer_function(philo, 1);
		else
			return ;
		register_last_meal(&philo);
		ft_sleep(philo->data, philo->data->time_to_eat, philo);
		mutex_unlock(philo->left_mutex);
		mutex_unlock(&philo->mutex);
	}
}

void	sleeping(struct s_philos *philo)
{
	mutex_lock(&philo->sleep_mutex);
	ft_sleep(philo->data, philo->data->time_to_sleep, philo);
	mutex_unlock(&philo->sleep_mutex);
}

void	thinking(struct s_philos *philo)
{
	mutex_lock(&philo->think_mutex);
	if (philo->is_alive == 1)
		printer_function(philo, 0);
	else
		return ;
	mutex_unlock(&philo->think_mutex);
}
