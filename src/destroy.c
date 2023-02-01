
#include "../include/philo.h"

void	destroy_data(struct s_data *data)
{
	int				i;	
	struct s_philos	*philos;

	i = 0;
	while (i < data->number_of_philos)
	{
		philos = &data->philosophers[i++];
		free(philos);	
	}
	pthread_mutex_destroy(data->mutex);
	free(data);
}
