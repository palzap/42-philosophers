/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:47:13 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/04 08:09:12 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_message(t_data *data, int i)
{
	unsigned int	time;

	usleep(100);
	time = get_time() - data->start;
	sem_wait(data->message);
	if (i == 1)
		printf("%u %d %s", time, data->philos[data->index].id,
			"has taken a fork\n");
	if (i == 2)
		printf("%u %d %s", time, data->philos[data->index].id, "is eating\n");
	if (i == 3)
		printf("%u %d %s", time, data->philos[data->index].id, "is sleeping\n");
	if (i == 4)
		printf("%u %d %s", time, data->philos[data->index].id, "is thinking\n");
	if (i == 5)
		printf("%u %d %s", time, data->philos[data->index].id, "died\n");
	sem_post(data->message);
}

void	take_forks(t_data *data)
{
	usleep(100);
	sem_wait(data->forks);
	print_message(data, 1);
	usleep(100);
	sem_wait(data->forks);
	print_message(data, 1);
}

void	eating(t_data *data)
{
	take_forks(data);
	sem_wait(data->philos[data->index].can_die);
	print_message(data, 2);
	data->philos[data->index].last_meal = get_time();
	sem_post(data->philos[data->index].can_die);
	usleep(data->time_to_eat * 1000);
	sem_post(data->forks);
	sem_post(data->forks);
	data->philos[data->index].meal_number++;
	if (data->philos[data->index].meal_number == data->must_eat
		&& data->must_eat != -1)
		sem_post(data->meals);
}

void	sleeping(t_data *data)
{
	print_message(data, 3);
	usleep(data->time_to_sleep * 1000);
}
