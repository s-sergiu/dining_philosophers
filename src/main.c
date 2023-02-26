
#include "../include/philo.h"

void	printer_function(struct s_philos *philo, int state)
{
	if (state == 1)
		printf("\e[1;32m %ld ms\t%d is eating\e[0m\n", get_time(philo->data), philo->id);
	else if (state == 2)
		printf("\e[1;35m %ld ms\t%d is thinking\e[0m\n", get_time(philo->data), philo->id);
	else
		printf("\e[1;34m %ld ms\t%d is sleeping\e[0m\n", get_time(philo->data), philo->id);
		
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
