/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:11:22 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/27 17:36:55 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	free(data->philos[0].forks);
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
