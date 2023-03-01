/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:43:37 by rabustam          #+#    #+#             */
/*   Updated: 2023/03/01 15:41:00 by rabustam         ###   ########.fr       */
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

long int	print_action(t_philo *phi, int act)
{
	long int	time;

	time = get_current_time();
	pthread_mutex_lock(&phi->data->print_mutex);
	if (act == FORK)
		printf("%ld %d has taken a fork.\n%ld %d has taken a fork.\n", \
			time - phi->data->start_time, phi->id + 1, \
			time - phi->data->start_time, phi->id + 1);
	else if (act == EAT)
		printf("%ld %d is eating.\n", time - phi->data->start_time, phi->id + 1);
	else if (act == SLEEP)
		printf("%ld %d is sleeping.\n", time - phi->data->start_time, phi->id + 1);
	else if (act == THINK)
		printf("%ld %d is thinking.\n", time - phi->data->start_time, phi->id + 1);
	else if (act == DIE)
		printf("%ld %d died.\n", time - phi->data->start_time, phi->id + 1);
	pthread_mutex_unlock(&phi->data->print_mutex);
	return (time);
}

int	eating(t_philo *phi)
{
	pthread_mutex_lock(phi->l_fork);
	pthread_mutex_lock(phi->r_fork);
	if (has_died(phi))
	{
		pthread_mutex_unlock(phi->r_fork);
		pthread_mutex_unlock(phi->l_fork);
		return (-1);
	}
	
	print_action(phi, FORK);
	
	pthread_mutex_lock(&phi->data->last_meal_mutex);
	phi->last_meal = print_action(phi, EAT);
	pthread_mutex_unlock(&phi->data->last_meal_mutex);
	
	my_sleep(phi->data->time_to_eat, phi->last_meal);

	pthread_mutex_unlock(phi->r_fork);
	pthread_mutex_unlock(phi->l_fork);
	return (0);
}

int	sleeping(t_philo *phi)
{
	long int	time;

	if (has_died(phi))
		return (-1);
	time = print_action(phi, SLEEP);
	my_sleep(phi->data->time_to_sleep, time);
	return (0);
}

int	thinking(t_philo *phi)
{
	if (has_died(phi))
		return (-1);
	print_action(phi, THINK);
	return (0);
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
		sleeping(phi);
		thinking(phi);
	}
	pthread_mutex_lock(&phi->data->full_mutex);
		phi->is_full = 1;
	pthread_mutex_unlock(&phi->data->full_mutex);
	return (NULL);
}

static void	*check_time(void *ptr)
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
		if (lm_time >= data->time_to_die)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->has_anyone_died = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			print_action(&data->philos[i], DIE);
			return (NULL);
		}
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

int	launch_threads(t_info *data)
{
	pthread_t	*th;
	int			j;

	th = malloc((data->n_philos + 1) * sizeof(pthread_t));
	j = -1;
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
