/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:56:45 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/28 11:16:15 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	actions(t_data *data, t_philo *philos, int i)
{
	eating(data, &philos[i]);
	if (data->must_eat != philos[i].meal_number)
	{
		sleeping(data, &philos[i]);
		print_message(data, &philos[i], 4);
	}
	else
	{
		pthread_detach(data->death);
		pthread_detach(data->done);
		clean_up(data, philos);
		exit (0);
	}
}

void	processes(t_data *data, t_philo *philos)
{
	int	i;

	i = philos->id;
	if (data->philos == 1)
		sem_post(philos[i].can_die);
	pthread_create(&data->death, 0, death, philos + i);
	pthread_create(&data->done, 0, banquet_done, philos + i);
	while (((data->must_eat > philos[i].meal_number) && !data->dead)
		|| ((data->must_eat == -1) && !data->dead))
	{
		if (i % 2)
			usleep(1000);
		actions(data, philos, i);
	}
}