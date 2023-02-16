/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:20:19 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/16 15:31:59 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h> //-pthread flag necessary

typedef struct s_philo
{
	int	forks;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_count;
}	t_philo;

//functions
//philo_utils.c
int		philo_atoi(const char *nptr);
void	philo_bzero(void *s, size_t n);

//error.c
int		check_args(int argc, char **argv);
void	display_error_msg(int error);

#endif