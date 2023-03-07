/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssergiu <ssergiu@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:30:34 by ssergiu           #+#    #+#             */
/*   Updated: 2023/03/07 20:34:32 by ssergiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	odd_philos(struct s_philos *philo)
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

void	even_philos(struct s_philos *philo)
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

void	eating(struct s_philos *philo)
{
	if (philo->id % 2 == 0)
		even_philos(philo);
	else
		odd_philos(philo);
}

void	sleeping(struct s_philos *philo)
{
	printer_function(philo, 2);
	ft_sleep(philo->data, philo->data->time_to_sleep, philo);
	thinking(philo);
}

void	thinking(struct s_philos *philo)
{
	printer_function(philo, 0);
}
