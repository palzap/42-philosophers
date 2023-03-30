/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:00:20 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/30 09:20:51 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

unsigned int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*death_check(void *arg)
{
	unsigned int	time;
	t_data			*data;

	data = (t_data *)arg;	
	while (1)
	{
		time = get_time() - data->philos[data->index].last_meal;
		if (time > (unsigned int)data->time_to_die)
		{
			sem_wait(&data->philos[data->index].can_die);
			print_message(data, 5);
			sem_post(data->finish);
			sem_post(&data->philos[data->index].can_die);
			exit (0);
		}
	}
	return (0);
}

void	processes(t_data *data)
{
	pthread_t	reaper;
	
	if (data->index % 2)
		usleep(1000);
	data->philos[data->index].last_meal = get_time();
	pthread_create(&reaper, 0, death_check, data);
	while (1)
	{
		eating(data);
		sleeping(data);
		print_message(data, 4);
	}
	return ;
}
