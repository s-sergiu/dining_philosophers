
#include "../include/philo.h"

int main(int argc, char **argv)
{
	struct s_data	*data;	
	struct s_philos	*philos;
	int				input_is_valid;

	input_is_valid = FALSE;
	if (argc != 5 && argc != 6)
		write(1, "Usage\n", 6);
	else 
	{
		parse_input(argv, &input_is_valid);
		if (input_is_valid)
		{
			init_data(&data, argv);
			init_philos(&philos, data); 
		}
		printf("argv: %s\n", argv[1]);
	}
	return(TRUE);
}
