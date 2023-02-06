
#include "../include/philo.h"

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
			destroy_data(data);
		}
		printf("Input was %d\n", input_is_valid);
	}
	return(TRUE);
}
