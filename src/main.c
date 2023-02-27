
#include "../include/philo.h"

void	printer_function(struct s_philos *philo, int state)
{
	int	id;

	id = philo->id;
	if (state == 1)
	{
		printf("\e[1;32m %ld\t%d has taken a fork\e[0m\n", get_time(philo->data), id);
		printf("\e[1;32m %ld\t%d is eating\e[0m\n", get_time(philo->data), id);
	}
	else if (state == 2)
		printf("\e[1;35m %ld\t%d is sleeping\e[0m\n", get_time(philo->data), id);
	else
		printf("\e[1;34m %ld\t%d is thinking\e[0m\n", get_time(philo->data), id);
		
}

int main(int argc, char **argv)
{
	struct s_data	*data;	
	int				input_is_valid;

	data = NULL;
	input_is_valid = FALSE;
	if (argc != 5 && argc != 6)
		write(1, "Usage\n", 6);
	else 
	{
		parse_input(argv, &input_is_valid);
		if (input_is_valid)
		{
			init_data(&data, argv);
			init_philos(data); 
			//destroy_data(data);
		}
		if (input_is_valid)
			printf("Input was valid\n");
		else
			printf("Input was invalid\n");
	}
	return(TRUE);
}
