/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssergiu <ssergiu@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:30:37 by ssergiu           #+#    #+#             */
/*   Updated: 2023/03/07 20:30:39 by ssergiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

struct s_data
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_eats;
	struct s_philos		*philosophers;
	pthread_mutex_t		global_mutex;
	pthread_mutex_t		routine_mutex;
	pthread_mutex_t		gettime_mutex;
	struct timeval		t1;
	int					philo_dead;
	long				starting_time;
};

struct s_philos
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	sleep_mutex;
	pthread_mutex_t	think_mutex;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*left_mutex;
	struct s_data	*data;
	int				number;
	struct timeval	t2;
	long			time2;
	long			last_meal;
	long			fed;
};

// main functions

void	thinking(struct s_philos *philo);
void	sleeping(struct s_philos *philo);
void	eating(struct s_philos *philo);
void	parse_input(char **argv, int *flag);
void	init_data(struct s_data **data, char **argv);
void	init_philos(struct s_data *data);
void	destroy_data(struct s_data *data);
long	atoi_philo(char *string);
void	custom_time(int ms);
void	mutex_lock(pthread_mutex_t *mutex);
void	mutex_unlock(pthread_mutex_t *mutex);
void	ft_sleep(struct s_data *data, int ms, struct s_philos *philo);
long	get_time(struct s_data *data);
void	printer_function(struct s_philos *philo, int state);
void	register_last_meal(struct s_philos **philo);
int		is_dead(struct s_philos *philo, int flag);
int		numbers_are_incorrect(struct s_data *data);
void	look_for_dead(struct s_data *data, struct s_philos *philos);

// debug functions
void	print_data(struct s_data *data);

#endif
