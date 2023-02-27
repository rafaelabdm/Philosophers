/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:43:37 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/27 15:44:04 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	has_died(t_philo *phi)
{
	long int	time;

	time = get_current_time(phi->data->start_time) - phi->last_meal;
	if (time >= phi->data->time_to_die)
	{
		printf("%ld %d has died.\n", get_current_time(phi->data->start_time), \
		phi->id + 1);
		return (1);
	}
	return (0);
}

void	*routine2(void *ptr)
{
	t_philo	*phi;

	phi = (t_philo *)ptr;
	while (!has_died(phi))
	{
		pthread_mutex_lock(&phi->forks[phi->id]);
		pthread_mutex_lock(&phi->forks[(phi->id + 1) % phi->data->n_philos]);
		
		printf("%ld %d has taken a fork.\n", get_current_time(phi->data->start_time), phi->id + 1);
		printf("%ld %d has taken a fork.\n", get_current_time(phi->data->start_time), phi->id + 1);
		printf("%ld %d is eating.\n", get_current_time(phi->data->start_time), phi->id + 1);
		phi->last_meal = get_current_time(phi->data->start_time);
		usleep(phi->data->time_to_eat * 1000);
		
		pthread_mutex_unlock(&phi->forks[phi->id]);
		pthread_mutex_unlock(&phi->forks[(phi->id + 1) % phi->data->n_philos]);
		
		printf("%ld %d is sleeping.\n", get_current_time(phi->data->start_time), phi->id + 1);
		usleep(phi->data->time_to_sleep * 1000);

		printf("%ld %d is thinking.\n", get_current_time(phi->data->start_time), phi->id + 1);
	}
	return (NULL);
}

int	launch_threads(t_info *data)
{
	pthread_t	*th;
	int			j;

	th = malloc(data->n_philos * sizeof(pthread_t));
	j = -1;
	data->start_time = get_start_time();
	while (++j < data->n_philos)
	{
		if (pthread_create(&th[j], NULL, &routine2, &data->philos[j]))
			return (1);
	}
	j = -1;
	while (++j < data->n_philos)
	{
		if (pthread_join(th[j], NULL))
			return (2);
	}
	free(th);
	return (0);
}
