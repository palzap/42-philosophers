/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:04:34 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/29 20:10:26 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	death(t_philo *philo)
{
	unsigned int	time;
	int				i;

	i = 0;
	while (i < philo->data->philos)
	{
		time = get_time() - philo[i].last_meal;
		if (time > (unsigned int)philo->data->time_to_die)
		{
			pthread_mutex_lock(&philo->reaper);
			print_message(&philo[i], 5);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->reaper);
			return (1);
		}
		i++;
	}
	return (0);
}
