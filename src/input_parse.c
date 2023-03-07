
#include "../include/philo.h"

int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	is_not_valid_number(char *argv)
{
	int	i;	

	i = -1;
	if (argv[0] == '0' && argv[1] == 0)
		return (1);
	while (argv[++i] != 0)
	{
		if (!ft_isdigit(argv[i]))
			return (1);
	}
	return (0);
}

void	parse_input(char **argv, int *flag)
{
	int	i;

	i = 0;
	while (argv[++i])
		if (is_not_valid_number(argv[i]))
			return ;
	*flag = TRUE;
}
