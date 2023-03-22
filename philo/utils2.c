/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:04:34 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/22 12:55:55 by pealexan         ###   ########.fr       */
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
			print_message(&philo[i], 5);
			philo->data->dead = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	join_threads(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < data->philos)
	{
		if (pthread_join(philos[i].id, NULL) != 0)
		{
			clean_up(data, forks, philos);
			return (print_error("Thread join failed at philos\n"));
		}
	}
	return (1);
}
