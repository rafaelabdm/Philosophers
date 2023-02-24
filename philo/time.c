/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:27:24 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/24 22:06:59 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//test function that shows time in miliseconds
	//1 microsecond == 0,001 milisecond
	//1 second == 1000 miliseconds

long int		get_start_time(void)
{
	struct timeval	start_time;
	long int		ret;

	gettimeofday(&start_time, NULL);
	ret = start_time.tv_sec * 1000 + start_time.tv_usec / 1000;
	return (ret);
}

long int	get_current_time(long int start)
{
	struct timeval	end_time;
	long int		end;

	gettimeofday(&end_time, NULL);
	end = end_time.tv_sec * 1000 + end_time.tv_usec / 1000;
	return (end - start);
}
