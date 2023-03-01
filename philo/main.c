/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:11:22 by rabustam          #+#    #+#             */
/*   Updated: 2023/03/01 14:28:17 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_info *data)
{
	int	i;

	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->full_mutex);
	pthread_mutex_destroy(&data->last_meal_mutex);
	i = -1;
	while (++i < data->n_philos)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	free(data->philos);
}

void	*one_routine(void *info)
{
	long int		current_time;
	t_info			*data;

	data = (t_info *)info;
	data->start_time = get_current_time();
	printf("%d 1 has taken a fork\n", 0);
	usleep(data->time_to_die * 1000);
	current_time = get_current_time();
	printf("%ld 1 died\n", current_time - data->start_time);
	return (NULL);
}

int	handle_one_thread(t_info *data)
{
	pthread_t	t1;

	if (pthread_create(&t1, NULL, &one_routine, data))
		return (1);
	if (pthread_join(t1, NULL))
		return (2);
	free_all(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	data;
	int		error;

	philo_bzero(&data, sizeof(t_info));
	error = init_data(argc, argv, &data);
	if (error != 0)
	{
		display_error_msg(error);
		return (1);	
	}
	if (data.n_philos == 1)
		return (handle_one_thread(&data));
	if (launch_threads(&data))
		return (1);
	free_all(&data);
	return (0);
}
