/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:56:45 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/23 21:49:20 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	actions(t_data *data, t_philo *philo)
{
	eating(data, philo);
	if (data->must_eat != philo->meal_number)
	{
		sleeping(data, philo);
		print_message(data, philo, 4);
	}
	else
	{
		pthread_detach(data->death);
		pthread_detach(data->done);
		clean_up(data, philo);
		exit (0);
	}
}

void	processes(t_data *data, t_philo *philos)
{
	if (data->philos == 1)
	{
		sem_post(philos->can_die);
		/* print_message(data, philo, 1);
		usleep(data->time_to_die * 1000);
		print_message(data, philo, 5);
		clean_up(data, philo);
		exit (0); */
	}
	pthread_create(&data->death, 0, death, philos);
	pthread_create(&data->done, 0, banquet_done, philos);
	while ((philos->data->must_eat > philos->meal_number)
		|| (philos->data->must_eat == -1))
		actions(data, philos);
}