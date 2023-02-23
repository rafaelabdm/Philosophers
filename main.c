/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:11:22 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/23 15:23:46 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_philos(t_info *data)
{
	(void) data;
	return (0);
}

static int	init_data(int argc, char **argv, t_info *data)
{
	int	args_err;

	if (argc < 5 || argc > 6)
		return (-1);
	args_err = check_args(argc, argv);
	if (args_err != 0)
		return (args_err);
	data->forks = philo_atoi(argv[1]);
	if (data->forks == 0)
		return (-4);
	data->time_to_die = philo_atoi(argv[2]);
	data->time_to_eat = philo_atoi(argv[3]);
	data->time_to_sleep = philo_atoi(argv[4]);
	if (argc == 6)
		data->eat_count = philo_atoi(argv[5]);
	if (data->time_to_die == -1 || data->time_to_eat == -1 || \
	data->time_to_sleep == -1 || data->eat_count == -1)
		return (-3);
	init_philos(data);
	return (0);
}

//prints to see if values are right:
// printf("philosophers/forks: %i\n", philos.forks);
// printf("time to die: %i\n", philos.time_to_die);
// printf("time to eat: %i\n", philos.time_to_eat);
// printf("time to sleep: %i\n", philos.time_to_sleep);
// printf("number of times each philosopher must eat: %i\n", philos.eat_count);

int	main(int argc, char **argv)
{
	t_info	data;
	int		error;

	philo_bzero(&data, sizeof(t_info));
	error = init_data(argc, argv, &data);
	if (error != 0)
		display_error_msg(error);
	if (launch_threads(&data))
	{
		printf("Error while creating a thread!\n");
		return (1);
	}
	return (0);
}
