/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:11:22 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/27 14:45:54 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*alloc_forks(int n_philos)
{
	pthread_mutex_t	*ret;

	ret = malloc(n_philos * sizeof(pthread_mutex_t));
	if (!ret)
		exit(11);
	return (ret);
}

static int	init_philos(t_info *data)
{
	t_philo	*temp_ph;
	int		i;
	pthread_mutex_t	*philo_forks;

	i = 0;
	temp_ph = malloc(data->n_philos * sizeof(t_philo));
	philo_forks = alloc_forks(data->n_philos);
	while (i < data->n_philos)
	{
		temp_ph[i].forks = philo_forks;
		pthread_mutex_init(&philo_forks[i], NULL);
		temp_ph[i].id = i;
		temp_ph[i].is_eating = FALSE;
		temp_ph[i].last_meal = 200;
		temp_ph[i].data = data;
		i++;
	}
	data->philos = temp_ph;
	return (0);
}

static int	init_data(int argc, char **argv, t_info *data)
{
	int	args_err;

	data->start_time = 0;
	data->philos = NULL;
	if (argc < 5 || argc > 6)
		return (-1);
	args_err = check_args(argc, argv);
	if (args_err != 0)
		return (args_err);
	data->n_philos = philo_atoi(argv[1]);
	if (data->n_philos == 0)
		return (-4);
	data->time_to_die = philo_atoi(argv[2]);
	data->time_to_eat = philo_atoi(argv[3]);
	data->time_to_sleep = philo_atoi(argv[4]);
	if (argc == 6)
		data->eat_count = philo_atoi(argv[5]);
	else
		data->eat_count = -42;
	if (data->time_to_die == -1 || data->time_to_eat == -1 || \
	data->time_to_sleep == -1 || data->eat_count == -1)
		return (-3);
	data->time_to_think = data->time_to_die - data->time_to_sleep - data->time_to_eat;
	init_philos(data);
	return (0);
}

void	*one_routine(void *info)
{
	long int		current_time;
	t_info			*data;

	data = (t_info *)info;
	data->start_time = get_start_time();
	printf("%d 1 is thinking\n", 0);
	usleep(data->time_to_die * 1000);
	current_time = get_current_time(data->start_time);
	printf("%ld 1 died\n", current_time);
	return (NULL);
}

void	handle_one_thread(t_info *data)
{
	pthread_t	t1;

	if (pthread_create(&t1, NULL, &one_routine, data))
		exit(1);
	if (pthread_join(t1, NULL))
		exit(2);
	free(data->philos);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_info	data;
	int		error;

	philo_bzero(&data, sizeof(t_info));
	error = init_data(argc, argv, &data);
	if (error != 0)
		display_error_msg(error);
	if (data.n_philos == 1)
		handle_one_thread(&data);
	if (launch_threads(&data))
	{
		printf("Error while creating a thread!\n");
		return (1);
	}
	free(data.philos);
	return (0);
}
