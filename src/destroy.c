
#include "../include/philo.h"

void	destroy_data(struct s_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
		free(data->philosophers[i].thread);
	i = -1;
	while (++i < data->number_of_philos)
	{
		pthread_mutex_destroy(data->philosophers[i].mutex);
		free(data->philosophers[i].mutex);
	}
	free(data->philosophers);
	free(data);
}
