/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:20:19 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/24 15:15:42 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h> //-pthread flag necessary
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	int	l_fork;
	int	r_fork;
	int	is_eating;
	int	last_meal;
}	t_philo;

typedef struct s_info
{
	int			forks;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eat_count;
	long int	start_time;
	t_philo		*philos;
}	t_info;

//functions
//philo_utils.c
int			philo_atoi(const char *nptr);
void		philo_bzero(void *s, size_t n);

//error.c
int			check_args(int argc, char **argv);
void		display_error_msg(int error);

//threads.c
int			launch_threads(t_info *philos);

//time.c
long int	get_start_time(void);
long int	get_current_time(long int start);
#endif