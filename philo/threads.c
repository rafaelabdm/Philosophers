/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:43:37 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/24 16:43:33 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine2(void *ptr)
{
	t_philo	*phi;

	phi = (t_philo *)ptr;
	// printf("Thread %d my_fork %d.\n", phi->id, phi->my_fork);
	// printf("Thread %d next_fork %d.\n", phi->id, phi->next_fork);
	// printf("Thread %d is eating %d.\n", phi->id, phi->is_eating);
	// printf("Thread %d last meal %d.\n", phi->id, phi->last_meal);
	if (phi->my_fork && phi->next_fork)
		printf("Thread %d is eating!\n", phi->id);
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
		if (pthread_create(&th[j], NULL, &routine2, &data->philos[j]))
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
