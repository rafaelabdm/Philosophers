/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:27:24 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/23 14:28:51 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//test function that shows time in miliseconds
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
