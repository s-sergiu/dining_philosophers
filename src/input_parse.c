/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssergiu <ssergiu@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:31:13 by ssergiu           #+#    #+#             */
/*   Updated: 2023/03/07 20:32:42 by ssergiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	numbers_are_incorrect(struct s_data *data)
{
	if (data->number_of_philos == -1)
		return (TRUE);
	if (data->time_to_die < 60)
		return (TRUE);
	if (data->time_to_eat < 60)
		return (TRUE);
	if (data->time_to_sleep < 60)
		return (TRUE);
	if (data->number_of_eats < 0)
		return (TRUE);
	return (FALSE);
}
