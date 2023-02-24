/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:43:37 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/23 15:38:04 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine2(void *ptr)
{
	t_philo	*phi;

	phi = (t_philo *)ptr;
	printf("Threads l_fork %d.\n", phi->l_fork);
	printf("Threads r_fork %d.\n", phi->r_fork);
	printf("Threads is eating %d.\n", phi->is_eating);
	printf("Threads last meal %d.\n", phi->last_meal);
	return (NULL);
}

int	launch_threads(t_info *data)
{
	pthread_t	*th;
	int			j;

	th = malloc(data->forks * sizeof(pthread_t));
	j = -1;
	while (++j < data->forks)
	{
		if (pthread_create(&th[j], NULL, &routine2, data->philos))
			return (1);
	}
	j = -1;
	while (++j < data->forks)
	{
		if (pthread_join(th[j], NULL))
			return (2);
	}
	free(th);
	return (0);
}
