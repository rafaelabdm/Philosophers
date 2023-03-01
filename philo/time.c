/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:27:24 by rabustam          #+#    #+#             */
/*   Updated: 2023/03/01 14:59:26 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//test function that shows time in miliseconds
	//1 microsecond == 0,001 milisecond
	//1 second == 1000 miliseconds

long int	get_current_time(void)
{
	struct timeval	start_time;
	long int		ret;

	gettimeofday(&start_time, NULL);
	ret = start_time.tv_sec * 1000 + start_time.tv_usec / 1000;
	return (ret);
}

void	my_sleep(int sleep, long int last_meal)
{
	long int	start;

	start = get_current_time();
	while (start - last_meal < sleep)
	{
		start = get_current_time();
		usleep(100);
	}
}
