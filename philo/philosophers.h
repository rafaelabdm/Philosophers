/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:20:19 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/28 14:49:22 by rabustam         ###   ########.fr       */
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

# define THINK "is thinking"
# define SLEEP "is sleeping"
# define FORK "has taken a fork"
# define EAT "is eating"
# define DIE "has died"

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*forks;
	int				last_meal;
	int				is_full;
	struct s_info	*data;
}	t_philo;

typedef struct s_info
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	int				has_anyone_died;
	long int		start_time;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	full_mutex;
	pthread_mutex_t	last_meal_mutex;
}	t_info;

//functions
//init.c
int			init_data(int argc, char **argv, t_info *data);

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