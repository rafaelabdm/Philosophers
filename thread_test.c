/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:43:37 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/23 13:38:05 by rabustam         ###   ########.fr       */
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

// gcc -Wall -Wextra -Werror -pthread thread_test.c
int	main(int argc, char **argv)
{
	pthread_t *th;
	int	j;
	int	count;

	if (argc != 2)
		return (1);
	count = philo_atoi(argv[1]);
	th = malloc(count * sizeof(pthread_t));
	j = -1;
	while (++j < count)
	{
		int	*i;
		i = malloc(sizeof(int));
		*i = j;
		if (pthread_create(&th[j], NULL, &routine2, (void *)i))
			return (1);
	}
	j = -1;
	while (++j < count)
	{
		if (pthread_join(th[j], NULL)) //wait for threads
			return (2);
	}
	free(th);
	return (0);
}