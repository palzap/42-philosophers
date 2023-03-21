/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:04:34 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/21 14:19:39 by pealexan         ###   ########.fr       */
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
    unsigned int    i;

    i = get_time() - philo->last_meal;
    if (i > (unsigned int)philo->data->time_to_die)
    {
        print_message(philo, 5);
        philo->data->dead = 1;
        return (1);
    }
    return (0);
}