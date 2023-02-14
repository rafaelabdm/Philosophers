/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_study.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:11:22 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/14 18:58:07 by rabustam         ###   ########.fr       */
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
			return (-1);
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

int	philo_atoi(const char *nptr)
{
	int				i;
	unsigned int	ret;

	i = 0;
	ret = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		ret = ret * 10 + (nptr[i] - 48);
		i++;
	}
	if (ret > 2147483647)
		return (-1);
	return ((int) ret);
}

void	ft_bzero(void *s, size_t n)
{
	char	*s_cpy;

	s_cpy = s;
	while (n--)
		*s_cpy++ = 0;
}

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

void	display_error_msg(int error)
{
	if (error == -1)
			printf("\nError: Wrong number of arguments.\n");	
		else if (error == -2)
			printf("\nError: Neither time nor people can be negative. C'mon man...\n");
		else if (error == -3)
			printf("\nError: Time must be an integer. Remember to respect the boundries.\n");
		else if (error == -4)
			printf("\nError: There must be at least one philosopher in the sim.\n");
		printf("Usage: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n\n");
		exit(1);
}

int main(int argc, char **argv)
{
	t_philo	philos;
	int		error;

	ft_bzero(&philos, sizeof(t_philo));
	error = init_philos(argc, argv, &philos);
	if (error != 0)
		display_error_msg(error);
	printf("philosophers/forks: %i\n", philos.forks);
	printf("time to die: %i\n", philos.time_to_die);
	printf("time to eat: %i\n", philos.time_to_eat);
	printf("time to sleep: %i\n", philos.time_to_sleep);
	printf("number of times each philosopher must eat: %i\n", philos.eat_count);
	return (0);	
}
