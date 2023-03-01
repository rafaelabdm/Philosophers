/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:27:24 by rabustam          #+#    #+#             */
/*   Updated: 2023/03/01 16:23:51 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//1 microsecond == 0,001 milisecond
//1 second == 1000 miliseconds

long int	get_current_time(void)
{
	struct timeval	start_time;
	long int		ret;

	gettimeofday(&start_time, NULL);
	ret = start_time.tv_sec * 1000 + start_time.tv_usec / 1000;
	return (ret);
}

void	my_sleep(int sleep, long int last_meal)
{
	long int	start;

	start = get_current_time();
	while (start - last_meal < sleep)
	{
		start = get_current_time();
		usleep(100);
	}
}

static int	kill_philo(t_info *data, long int lm_time, int i)
{
	if (lm_time >= data->time_to_die)
	{
		pthread_mutex_lock(&data->stop_mutex);
		data->has_anyone_died = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		philo_print(&data->philos[i], DIE);
		return (1);
	}
	return (0);
}

void	*check_time(void *ptr)
{
	t_info		*data;
	long int	lm_time;
	int			i;

	data = (t_info *)ptr;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->last_meal_mutex);
		lm_time = get_current_time() - data->philos[i].last_meal;
		pthread_mutex_unlock(&data->last_meal_mutex);
		if (kill_philo(data, lm_time, i))
			return (NULL);
		pthread_mutex_lock(&data->full_mutex);
		if (data->philos[i].is_full)
		{
			pthread_mutex_unlock(&data->full_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->full_mutex);
		if (++i == data->n_philos)
			i = 0;
		usleep(2500);
	}
	return (NULL);
}
