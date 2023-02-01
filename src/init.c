
#include "../include/philo.h"

void	init_data(struct s_data **data, char **argv)
{
	(*data) = malloc(sizeof(struct s_data));
	(*data)->number_of_philos = atoi(argv[1]);
	(*data)->time_to_die = atoi(argv[2]);
	(*data)->time_to_eat = atoi(argv[3]);
	(*data)->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		(*data)->number_of_eats = atoi(argv[5]);
	write(1, "Data initialized\n", 17);
}

void	init_philos(struct s_philos **philos, struct s_data *data)
{
	int	i;

	i = 0;
	(*philos) = malloc(sizeof(struct s_philos) * data->number_of_philos);
	while (i < data->number_of_philos)
	{
		i++;
	}
}
