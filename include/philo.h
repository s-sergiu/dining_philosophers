
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

#define TRUE 1
#define FALSE 0

struct s_data 
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eats;
	struct s_philos	**philosophers;
	pthread_mutex_t	*mutex;
};

struct s_philos 
{
	int			id;
	pthread_t	thread;
	pthread_mutex_t *mutex;
};

void	parse_input(char **argv, int *flag);
void	init_data(struct s_data **data, char **argv);
void	init_philos(struct s_data *data);

#endif
