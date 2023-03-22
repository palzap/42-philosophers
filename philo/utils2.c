/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:04:34 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/22 08:15:51 by pealexan         ###   ########.fr       */
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
	int	i;

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
