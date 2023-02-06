
#include "../include/philo.h"

long	atoi_philo(char *string)
{
	long	number;
	int		i;

	i = -1;
	number = 0;
	while (string[++i])
		number = number * 10 + (string[i] - '0');
	if (number > 2147483647)
		return (-1);
	return (number);
}
