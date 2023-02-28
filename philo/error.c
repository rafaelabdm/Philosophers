/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:22:29 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/28 13:57:10 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '\0')
			return (-5);
		j = 0;
		if (argv[i][0] == '-' || argv[i][0] == '+')
		{
			if (argv[i][0] == '-')
				return (-2);
			j++;
		}
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (-3);
			j++;
		}
	}
	return (0);
}

void	display_error_msg(int error)
{
	if (error == -1)
		printf("\nError: Wrong number of arguments.\n");
	else if (error == -2)
		printf("\nError: Neither time(s) nor people can be negative. \
C'mon man...\n");
	else if (error == -3)
		printf("\nError: Arguments must be integers greater than zero. \
Remember to respect the boundries.\n");
	else if (error == -5)
		printf("\nError: Empty string? Realy???\n");
	printf("Usage: number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n\n");
}
