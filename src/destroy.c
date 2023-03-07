
#include "../include/philo.h"

void	destroy_data(struct s_data *data)
{
	free(data->philosophers);
	free(data);
}
