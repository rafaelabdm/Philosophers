/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:43:37 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/27 17:50:20 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	has_died(t_philo *phi)
{
	int ret;

	ret = 0;
	pthread_mutex_lock(&phi->data->stop_mutex);
	if (phi->data->has_anyone_died == 1)
		ret = 1;
	pthread_mutex_unlock(&phi->data->stop_mutex);
	return (ret);
}

void	print_action(t_philo *phi, int act)
{
	if (has_died(phi))
		return ;
	pthread_mutex_lock(&phi->data->print_mutex);
	if (act == EAT)
		printf("%ld %d is eating.\n", get_current_time(phi->data->start_time), phi->id + 1);
	else if (act == SLEEP)
		printf("%ld %d is sleeping.\n", get_current_time(phi->data->start_time), phi->id + 1);
	else if (act == THINK)
		printf("%ld %d is thinking.\n", get_current_time(phi->data->start_time), phi->id + 1);
	else if (act == FORK)
		printf("%ld %d has taken a fork.\n", get_current_time(phi->data->start_time), phi->id + 1);
	else if (act == DIE)
		printf("%ld %d has died.\n", get_current_time(phi->data->start_time), phi->id + 1);
	pthread_mutex_unlock(&phi->data->print_mutex);
}

void	eating(t_philo *phi)
{
	pthread_mutex_lock(&phi->forks[phi->id]);
	pthread_mutex_lock(&phi->forks[(phi->id + 1) % phi->data->n_philos]);
	print_action(phi, FORK);
	print_action(phi, FORK);
	phi->last_meal = get_current_time(phi->data->start_time);
	print_action(phi, EAT);
	usleep(phi->data->time_to_eat * 1000);
	pthread_mutex_unlock(&phi->forks[phi->id]);
	pthread_mutex_unlock(&phi->forks[(phi->id + 1) % phi->data->n_philos]);
}

static void	*routine(void *ptr)
{
	t_philo	*phi;
	int		count;

	phi = (t_philo *)ptr;
	count = -1;
	while (!has_died(phi) && \
	(++count < phi->data->eat_count || phi->data->eat_count == 0))
	{
		eating(phi);
		if (count + 1 == phi->data->eat_count)
			phi->is_full = 1;
		print_action(phi, SLEEP);
		usleep(phi->data->time_to_sleep * 1000);
		print_action(phi, THINK);
	}
	return (NULL);
}

static void	*check_time(void *ptr)
{
	t_info	*data;
	int		time;
	int		i;

	data = (t_info *)ptr;
	i = 0;
	while (!data->philos[i].is_full)
	{
		time = get_current_time(data->start_time);
		if (time - data->philos[i].last_meal >= data->time_to_die)
		{
			print_action(&data->philos[i], DIE);
			pthread_mutex_lock(&data->stop_mutex);
			data->has_anyone_died = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		i++;
		if (i == data->n_philos)
			i = 0;
	}
	return (NULL);
}

int	launch_threads(t_info *data)
{
	pthread_t	*th;
	int			j;

	th = malloc((data->n_philos + 1) * sizeof(pthread_t));
	j = -1;
	data->start_time = get_start_time();
	while (++j < data->n_philos)
	{
		if (pthread_create(&th[j], NULL, &routine, &data->philos[j]))
			return (1);
	}
	if (pthread_create(&th[j], NULL, &check_time, data))
			return (1);
	j = -1;
	while (++j < data->n_philos + 1)
	{
		if (pthread_join(th[j], NULL))
			return (2);
	}
	free(th);
	return (0);
}
