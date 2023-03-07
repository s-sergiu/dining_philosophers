/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssergiu <ssergiu@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:30:32 by ssergiu           #+#    #+#             */
/*   Updated: 2023/03/07 23:42:26 by ssergiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(struct s_data *data)
{
	long			current_time;
	long			start_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	mutex_lock(&data->gettime_mutex);
	start_time = (data->t1.tv_sec * 1000) + (data->t1.tv_usec / 1000);
	mutex_unlock(&data->gettime_mutex);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time - start_time);
}

int	philos_are_alive(struct s_philos *philo)
{
	mutex_lock(&philo->data->routine_mutex);
	if (philo->data->philo_dead == 1)
		return (FALSE);
	mutex_unlock(&philo->data->routine_mutex);
	eating(philo);
	mutex_lock(&philo->data->routine_mutex);
	if (philo->fed == philo->data->number_of_eats)
	{
		philo->data->print_flag = 0;
		return (FALSE);
	}
	mutex_unlock(&philo->data->routine_mutex);
	mutex_lock(&philo->data->routine_mutex);
	if (philo->data->philo_dead == 1)
		return (FALSE);
	mutex_unlock(&philo->data->routine_mutex);
	sleeping(philo);
	return (TRUE);
}

void	*routine(void *arg)
{
	struct s_philos	*philo;

	philo = arg;
	if (philo->left_mutex == NULL)
	{
		printf("0\t%d has taken a fork\n", philo->id);
		printf("%d\t%d has died\n", philo->data->time_to_die + 1, philo->id);
		return (NULL);
	}
	mutex_lock(&philo->data->global_mutex);
	mutex_unlock(&philo->data->global_mutex);
	mutex_lock(&philo->data->gettime_mutex);
	gettimeofday(&philo->data->t1, NULL);
	mutex_unlock(&philo->data->gettime_mutex);
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat);
	while (TRUE)
	{
		if (philos_are_alive(philo) == FALSE)
			break ;
	}
	mutex_unlock(&philo->data->routine_mutex);
	return (NULL);
}

void	create_philos(struct s_data *data, struct s_philos *philos)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		philos[i].id = i + 1;
		pthread_mutex_init(&philos[i].mutex, NULL);
		pthread_mutex_init(&philos[i].sleep_mutex, NULL);
		pthread_mutex_init(&philos[i].think_mutex, NULL);
		philos[i].data = data;
		philos[i].last_meal = 0;
		philos[i].fed = 0;
		if (i == 0 && data->number_of_philos != 1)
			philos[i].left_mutex = &philos[data->number_of_philos - 1].mutex;
		else if (data->number_of_philos != 1)
			philos[i].left_mutex = &data->philosophers[i - 1].mutex;
		else
			philos[i].left_mutex = NULL;
		philos[i].number = data->number_of_philos;
	}
}

void	init_philos(struct s_data *data)
{
	int				i;
	struct s_philos	*philos;

	mutex_lock(&data->global_mutex);
	philos = data->philosophers;
	if (numbers_are_incorrect(data) == TRUE)
	{
		printf("Numbers entered are not correct...\n");
		return ;
	}
	create_philos(data, philos);
	i = -1;
	while (++i < data->number_of_philos)
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
	i = -1;
	mutex_unlock(&data->global_mutex);
	while (++i < data->number_of_philos)
		pthread_join(philos[i].thread, NULL);
	look_for_dead(data, philos);
	return ;
}
