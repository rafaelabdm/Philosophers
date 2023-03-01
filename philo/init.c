/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:53:33 by rabustam          #+#    #+#             */
/*   Updated: 2023/03/01 15:22:45 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static pthread_mutex_t	*alloc_forks(int n_philos)
{
	pthread_mutex_t	*ret;

	ret = malloc(n_philos * sizeof(pthread_mutex_t));
	if (!ret)
		exit(11);
	return (ret);
}

static int	init_philos(t_info *data)
{
	t_philo			*temp_ph;
	int				i;
	pthread_mutex_t	*philo_forks;

	i = -1;
	temp_ph = malloc(data->n_philos * sizeof(t_philo));
	philo_forks = alloc_forks(data->n_philos);
	while (++i < data->n_philos)
		pthread_mutex_init(&philo_forks[i], NULL);
	data->forks = philo_forks;
	i = -1;
	while (++i < data->n_philos)
	{
		if (i + 1 == data->n_philos)
		{
			temp_ph[i].l_fork = &philo_forks[(i + 1) % data->n_philos];
			temp_ph[i].r_fork = &philo_forks[i];
		}
		else
		{
			temp_ph[i].l_fork = &philo_forks[i];
			temp_ph[i].r_fork = &philo_forks[(i + 1) % data->n_philos];
		}
		temp_ph[i].id = i;
		temp_ph[i].last_meal = data->start_time;
		temp_ph[i].is_full = 0;
		temp_ph[i].data = data;
	}
	data->philos = temp_ph;
	return (0);
}

static int	set_stats(int argc, char **argv, t_info *data)
{
	data->n_philos = philo_atoi(argv[1]);
	data->time_to_die = philo_atoi(argv[2]);
	data->time_to_eat = philo_atoi(argv[3]);
	data->time_to_sleep = philo_atoi(argv[4]);
	if (argc == 6)
		data->eat_count = philo_atoi(argv[5]);
	if (data->time_to_die == -1 || data->time_to_eat == -1 || \
	data->time_to_sleep == -1 || data->eat_count == -1 || \
	data->n_philos == -1)
		return (-3);
	return (0);
}

int	init_data(int argc, char **argv, t_info *data)
{
	int	args_err;

	if (argc < 5 || argc > 6)
		return (-1);
	args_err = check_args(argc, argv);
	if (args_err < 0)
		return (args_err);
	args_err = set_stats(argc, argv, data);
	if (args_err < 0)
		return (args_err);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->full_mutex, NULL);
	pthread_mutex_init(&data->last_meal_mutex, NULL);
	data->start_time = get_current_time();
	init_philos(data);
	return (0);
}
