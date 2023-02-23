/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:43:37 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/23 14:23:39 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//test function that shows time in miliseconds
// void	*routine()
// {
// 	struct timeval start_time;
// 	struct timeval finish_time;

// 	gettimeofday(&start_time, NULL);
// 	sleep(1);
// 	gettimeofday(&finish_time, NULL);
// 	//1 microsecond == 0,001 milisecond
// 	//o tempo que vou printar a mensagem - o tempo que começamos o programa = timestamp
// 	printf("miliseconds: %ld\n", ((finish_time.tv_sec * 1000 + finish_time.tv_usec / 1000) - \
// 	(start_time.tv_sec * 1000 + start_time.tv_usec / 1000)));
// 	printf("TESTE!\n");
// 	return (NULL);
// }

void	*routine2(void *ptr)
{
	int	index;

	index = *(int *)ptr;
	printf("Thread %d created.\n", index);
	free(ptr);
	return (NULL);
}

int	launch_threads(t_info *philos)
{
	pthread_t *th;
	int	j;

	th = malloc(philos->forks * sizeof(pthread_t));
	j = -1;
	while (++j < philos->forks)
	{
		int	*i;
		i = malloc(sizeof(int));
		*i = j;
		if (pthread_create(&th[j], NULL, &routine2, (void *)i))
			return (1);
	}
	j = -1;
	while (++j < philos->forks)
	{
		if (pthread_join(th[j], NULL)) //wait for threads
			return (2);
	}
	free(th);
	return (0);
}