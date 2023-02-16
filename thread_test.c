/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:43:37 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/16 18:22:03 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	printf("seconds : %ld\nmicro seconds : %ld\n", time.tv_sec, time.tv_usec);
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