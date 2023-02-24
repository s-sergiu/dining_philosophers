
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

#define TRUE 1
#define FALSE 0

struct s_data 
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eats;
	struct s_philos	*philosophers;
	pthread_mutex_t	global_mutex;
	pthread_mutex_t	routine_mutex;
	struct timeval	t1;
};

struct s_philos 
{
	int				id;
	int				*counter;
	int				*left_fork;
	int				fork;
	int				fed;
	pthread_t		*thread;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*left_mutex;;
	struct s_data	*data;
	int				number;
	struct timeval	t2;
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

// debug functions
void	print_data(struct s_data *data);

#endif
