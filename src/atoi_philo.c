/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssergiu <ssergiu@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:32:00 by ssergiu           #+#    #+#             */
/*   Updated: 2023/03/07 23:10:50 by ssergiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	atoi_philo(char *string)
{
	long	number;
	int		i;

	i = -1;
	number = 0;
	while (string[++i])
		number = number * 10 + (string[i] - '0');
	if (number > 2147483647)
		return (-1);
	return (number);
}

void	mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
		printf("Mutex failed to initialize\n");
}

void	mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
		printf("Mutex failed to initialize\n");
}

void	init_data(struct s_data **data, char **argv)
{
	int	number;

	(*data) = malloc(sizeof(struct s_data));
	(*data)->number_of_philos = atoi_philo(argv[1]);
	(*data)->time_to_die = atoi_philo(argv[2]);
	(*data)->time_to_eat = atoi_philo(argv[3]);
	(*data)->time_to_sleep = atoi_philo(argv[4]);
	if (argv[5])
		(*data)->number_of_eats = atoi(argv[5]);
	else
		(*data)->number_of_eats = 0;
	number = (*data)->number_of_philos;
	(*data)->philo_dead = 0;
	(*data)->print_flag = 1;
	(*data)->philosophers = malloc(sizeof(struct s_philos) * number);
	pthread_mutex_init(&(*data)->global_mutex, NULL);
	pthread_mutex_init(&(*data)->routine_mutex, NULL);
	pthread_mutex_init(&(*data)->gettime_mutex, NULL);
}

void	ft_sleep(struct s_data *data, int ms, struct s_philos *philo)
{
	long			initial_time;

	initial_time = get_time(data);
	if (data->philo_dead == 1)
		return ;
	while (get_time(data) - initial_time < ms)
	{
		mutex_lock(&data->routine_mutex);
		if (data->philo_dead == 1)
		{
			mutex_unlock(&data->routine_mutex);
			break ;
		}
		mutex_unlock(&data->routine_mutex);
		usleep(250);
		if (is_dead(philo, 0) == TRUE)
			break ;
	}
}
