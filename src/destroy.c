
#include "../include/philo.h"

void	destroy_data(struct s_data *data)
{
	pthread_mutex_destroy(data->mutex);
	free(data->mutex);
	free(data);
}
