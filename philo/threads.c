/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:43:37 by rabustam          #+#    #+#             */
/*   Updated: 2023/03/01 16:22:55 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	thinking(t_philo *phi)
{
	if (has_died(phi))
		return (-1);
	philo_print(phi, THINK);
	return (0);
}

void	*routine(void *ptr)
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

int	has_died(t_philo *phi)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&phi->data->stop_mutex);
	if (phi->data->has_anyone_died == 1)
		ret = 1;
	pthread_mutex_unlock(&phi->data->stop_mutex);
	return (ret);
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
	philo_print(phi, FORK);
	pthread_mutex_lock(&phi->data->last_meal_mutex);
	phi->last_meal = philo_print(phi, EAT);
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
	time = philo_print(phi, SLEEP);
	my_sleep(phi->data->time_to_sleep, time);
	return (0);
}
