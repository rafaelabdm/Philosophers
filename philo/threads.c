/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:43:37 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/28 14:50:31 by rabustam         ###   ########.fr       */
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

void	print_action(t_philo *phi, char *act)
{
	if (has_died(phi))
		return ;
	pthread_mutex_lock(&phi->data->print_mutex);
	printf("%ld %d %s.\n", get_current_time(phi->data->start_time), \
	phi->id + 1, act);
	pthread_mutex_unlock(&phi->data->print_mutex);
}

void	eating(t_philo *phi)
{
	if (phi->id + 1 == phi->data->n_philos)
	{
		pthread_mutex_lock(&phi->forks[(phi->id + 1) % phi->data->n_philos]);
		pthread_mutex_lock(&phi->forks[phi->id]);
	}
	else
	{
		pthread_mutex_lock(&phi->forks[phi->id]);
		pthread_mutex_lock(&phi->forks[(phi->id + 1) % phi->data->n_philos]);	
	}
	print_action(phi, FORK);
	print_action(phi, FORK);
	pthread_mutex_lock(&phi->data->last_meal_mutex);
	phi->last_meal = get_current_time(phi->data->start_time);
	pthread_mutex_unlock(&phi->data->last_meal_mutex);
	print_action(phi, EAT);
	usleep(phi->data->time_to_eat * 1000);
	pthread_mutex_unlock(&phi->forks[(phi->id + 1) % phi->data->n_philos]);
	pthread_mutex_unlock(&phi->forks[phi->id]);
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
		print_action(phi, SLEEP);
		usleep(phi->data->time_to_sleep * 1000);
		print_action(phi, THINK);
	}
	pthread_mutex_lock(&phi->data->full_mutex);
		phi->is_full = 1;
	pthread_mutex_unlock(&phi->data->full_mutex);
	return (NULL);
}

static void	*check_time(void *ptr)
{
	t_info	*data;
	int		time;
	int		i;

	data = (t_info *)ptr;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->last_meal_mutex);
		time = data->philos[i].last_meal;
		pthread_mutex_unlock(&data->last_meal_mutex);
		if (get_current_time(data->start_time) - time >= data->time_to_die)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->has_anyone_died = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			time =  get_current_time(data->start_time);
			pthread_mutex_lock(&data->print_mutex);
			printf("%d %d has died.\n", time, data->philos[i].id + 1);
			pthread_mutex_unlock(&data->print_mutex);
			break ;
		}
		pthread_mutex_lock(&data->full_mutex);
		if (data->philos[i].is_full)
		{
			pthread_mutex_unlock(&data->full_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->full_mutex);
		if (++i == data->n_philos)
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
	while (++j < data->n_philos)
	{
		data->start_time = get_start_time();
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
