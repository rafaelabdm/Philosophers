/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:43:37 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/23 15:27:14 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine2(void *ptr)
{
	t_info	*phi;

	phi = (t_info *)ptr;
	printf("Threads forks %d.\n", phi->forks);
	printf("Threads time to die %d.\n", phi->time_to_die);
	printf("Threads time to eat %d.\n", phi->time_to_eat);
	printf("Threads time to sleep %d.\n", phi->time_to_sleep);
	return (NULL);
}

int	launch_threads(t_info *philos)
{
	pthread_t	*th;
	int			j;

	th = malloc(philos->forks * sizeof(pthread_t));
	j = -1;
	while (++j < philos->forks)
	{
		if (pthread_create(&th[j], NULL, &routine2, philos))
			return (1);
	}
	j = -1;
	while (++j < philos->forks)
	{
		if (pthread_join(th[j], NULL))
			return (2);
	}
	free(th);
	return (0);
}
