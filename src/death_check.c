/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssergiu <ssergiu@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:32:10 by ssergiu           #+#    #+#             */
/*   Updated: 2023/03/07 22:50:25 by ssergiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	register_last_meal(struct s_philos **philo)
{
	struct timeval	time;

	if ((*philo)->last_meal == 0)
	{
		mutex_lock(&(*philo)->data->gettime_mutex);
		(*philo)->last_meal = ((*philo)->data->t1.tv_sec * 1000)
			+ ((*philo)->data->t1.tv_usec / 1000);
		mutex_unlock(&(*philo)->data->gettime_mutex);
	}
	else
	{
		gettimeofday(&time, NULL);
		(*philo)->last_meal = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	}
}

int	is_dead_from_the_beginning(struct s_philos *philo, int flag)
{
	long			current_time;

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

int	is_dead(struct s_philos *philo, int flag)
{
	struct timeval	time;
	long			current_time;

	if (philo->last_meal == 0)
	{
		if (is_dead_from_the_beginning(philo, flag))
			return (TRUE);
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

void	look_for_dead(struct s_data *data, struct s_philos *philos)
{
	int	i;

	while (1)
	{
		i = 0;
		while (++i < data->number_of_philos)
		{
			if (is_dead(&philos[i], data->print_flag) == TRUE)
				break ;
			if (i == data->number_of_philos - 1)
				i = -1;
		}
		return ;
	}
}
