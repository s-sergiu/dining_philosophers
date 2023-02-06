
#include "../include/philo.h"

void	destroy_data(struct s_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
		free(data->philosophers[i].thread);
	free(data->philosophers);
	pthread_mutex_destroy(data->mutex);
	free(data->mutex);
	free(data);
}
