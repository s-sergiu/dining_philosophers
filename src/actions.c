
#include "../include/philo.h"

void	register_last_meal(struct s_philos **philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	(*philo)->last_meal = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

int	is_dead(struct s_philos *philo, int flag)
{
	struct timeval	time;
	long			current_time;

	if (philo->last_meal == 0)
	{
		current_time = get_time(philo->data);
		mutex_lock(&philo->data->routine_mutex);
		if (current_time > philo->data->time_to_die)
		{
			if (flag == 1)
				printf("%ld\t%d died\n", get_time(philo->data), philo->id);
			philo->data->philo_dead = 1;
			mutex_unlock(&philo->data->routine_mutex);
			return (TRUE);
		}
		mutex_unlock(&philo->data->routine_mutex);
		return (FALSE);
	}
	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	mutex_lock(&philo->data->routine_mutex);
	if (current_time - philo->last_meal > philo->data->time_to_die)
	{
		if (flag == 1)
			printf("%ld\t%d died\n", get_time(philo->data), philo->id);
		philo->data->philo_dead = 1;
		mutex_unlock(&philo->data->routine_mutex);
		return (TRUE);
	}
	mutex_unlock(&philo->data->routine_mutex);
	return (FALSE);
}

void	eating(struct s_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		mutex_lock(philo->left_mutex);
		mutex_lock(&philo->mutex);
		printer_function(philo, 1);
		register_last_meal(&philo);
		philo->fed++;
		ft_sleep(philo->data, philo->data->time_to_eat, philo);
		mutex_unlock(&philo->mutex);
		mutex_unlock(philo->left_mutex);
	}
	else
	{
		mutex_lock(&philo->mutex);
		mutex_lock(philo->left_mutex);
		printer_function(philo, 1);
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
	ft_sleep(philo->data, 20, philo);
}
