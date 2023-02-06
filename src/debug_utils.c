
#include "../include/philo.h"

void	print_data(struct s_data *data)
{
	printf("number of philos %d\n", data->number_of_philos);
	printf("time to die %d\n", data->time_to_die);
	printf("time to eat %d\n", data->time_to_eat);
	printf("time to sleep %d\n", data->time_to_sleep);
	printf("number of eats %d\n", data->number_of_eats);
}

