/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:43:37 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/17 19:55:58 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine()
{
	struct timeval start_time;
	struct timeval finish_time;

	gettimeofday(&start_time, NULL);
	sleep(1);
	gettimeofday(&finish_time, NULL);
	//1 microsecond == 0,001 milisecond
	//o tempo que vou printar a mensagem - o tempo que começamos o programa = timestamp
	printf("miliseconds: %ld\n", ((finish_time.tv_sec * 1000 + finish_time.tv_usec / 1000) - \
	(start_time.tv_sec * 1000 + start_time.tv_usec / 1000)));
	printf("TESTE!\n");
	return (NULL);
}

int	main(void)
{
	int i = 1;
	pthread_t t1;
	if (pthread_create(&t1, NULL, &routine, &i))
		return (1);
	if (pthread_join(t1, NULL)) //wait for threads
		return (2);

	
	return (0);
}