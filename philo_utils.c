/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:19:13 by rabustam          #+#    #+#             */
/*   Updated: 2023/02/16 16:22:17 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_atoi(const char *nptr)
{
	int				i;
	int				z;
	unsigned int	ret;

	i = 0;
	z = 0;
	ret = 0;
	while (nptr[i] == '0')
	{
		i++;
		z++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		ret = ret * 10 + (nptr[i] - 48);
		i++;
	}
	if (ret > 2147483647 || i - z > 11)
		return (-1);
	return ((int) ret);
}

void	philo_bzero(void *s, size_t n)
{
	char	*s_cpy;

	s_cpy = s;
	while (n--)
		*s_cpy++ = 0;
}
