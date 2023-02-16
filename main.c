/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:11:22 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/16 15:46:44 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philos(int argc, char **argv, t_philo *philos)
{
	int	args_err;

	if (argc < 5 || argc > 6)
		return (-1);
	args_err = check_args(argc, argv);
	if (args_err != 0)
		return (args_err);
	philos->forks = philo_atoi(argv[1]);
	if (philos->forks == 0)
		return (-4);
	philos->time_to_die = philo_atoi(argv[2]);
	philos->time_to_eat = philo_atoi(argv[3]);
	philos->time_to_sleep = philo_atoi(argv[4]);
	if (argc == 6)
		philos->eat_count = philo_atoi(argv[5]);
	if (philos->time_to_die == -1 || philos->time_to_eat == -1 || \
	philos->time_to_sleep == -1 || philos->eat_count == -1)
		return (-3);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philos;
	int		error;

	philo_bzero(&philos, sizeof(t_philo));
	error = init_philos(argc, argv, &philos);
	if (error != 0)
		display_error_msg(error);
	printf("philosophers/forks: %i\n", philos.forks);
	printf("time to die: %i\n", philos.time_to_die);
	printf("time to eat: %i\n", philos.time_to_eat);
	printf("time to sleep: %i\n", philos.time_to_sleep);
	printf("number of times each philosopher must eat: %i\n", \
		philos.eat_count);
	return (0);
}
