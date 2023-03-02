/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:19:13 by rabustam          #+#    #+#             */
/*   Updated: 2023/03/02 15:47:45 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	philo_print(t_philo *phi, int act)
{
	long int	time;

	pthread_mutex_lock(&phi->data->print_mutex);
	time = get_current_time();
	if (act == FORK)
		printf("%ld %d has taken a fork.\n%ld %d has taken a fork.\n", \
			time - phi->data->start_time, phi->id + 1, \
			time - phi->data->start_time, phi->id + 1);
	else if (act == EAT)
		printf("%ld %d is eating.\n", time - phi->data->start_time, \
		phi->id + 1);
	else if (act == SLEEP)
		printf("%ld %d is sleeping.\n", time - phi->data->start_time, \
		phi->id + 1);
	else if (act == THINK)
		printf("%ld %d is thinking.\n", time - phi->data->start_time, \
		phi->id + 1);
	else if (act == DIE)
		printf("%ld %d died.\n", time - phi->data->start_time, phi->id + 1);
	pthread_mutex_unlock(&phi->data->print_mutex);
	return (time);
}

int	philo_atoi(const char *nptr)
{
	int				i;
	int				z;
	unsigned int	ret;

	i = 0;
	z = 0;
	ret = 0;
	if (nptr[i] == '+')
	{
		i++;
		z++;
	}
	while (nptr[i] == '0')
	{
		i++;
		z++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		ret = ret * 10 + (nptr[i] - 48);
		i++;
	}
	if (ret > 2147483647 || i - z > 11 || ret == 0)
		return (-1);
	return ((int) ret);
}

void	philo_bzero(void *s, size_t n)
{
	char	*s_cpy;

	s_cpy = s;
	while (n--)
		*s_cpy++ = 0;
}
