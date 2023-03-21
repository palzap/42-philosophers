/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:01:17 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/21 12:15:29 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *args)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)args;
	while (!banquet_done(philos))
	{
		i = -1;
		while (++i < philos->data->philos)
		{
			pthread_mutex_lock(&philos[i].reaper);
			if (death(&philos[i]))
			{
				print_message(philos, 5);
				philos->data->dead = 1;
				pthread_mutex_unlock(&philos[i].reaper);
				pthread_mutex_unlock(&philos[i].data->stop);
				return (0);
			}
			pthread_mutex_unlock(&philos[i].reaper);
			if (philos[i].meal_number == philos[i].data->must_eat)
				philos->data->all_ate++;
		}
	}
    printf("%u\tBanquet done after %d meals\n", get_time() - philos->start,
        philos->data->must_eat);
	return (0);
}

int	monitoring(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	pthread_t	monitoring;

	if (pthread_create(&monitoring, NULL, monitor, (void *)philos) != 0)
	{
		clean_up(data, forks, philos);
		return (print_error("Thread creation failed at monitoring\n"));
	}
	if (pthread_join(monitoring, NULL) != 0)
	{
		clean_up(data, forks, philos);
		return (print_error("Thread join failed at monitoring\n"));
	}
	return (1);
}

void	*assemble(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->data->dead && !banquet_done(philo))
	{
		if (philo->data->philos == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			print_message(philo, 1);
			philo->last_meal = get_time();
			return (0);
		}
		eating(philo);
		sleeping(philo);
		print_message(philo, 4);
	}
	return (0);
}

int	create_threads(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < data->philos)
	{
		philos[i].start = get_time();
		if (pthread_create(&philos[i].id, NULL, assemble, 
            (void *)&philos[i]) != 0)
		{
            clean_up(data, forks, philos);
			return (print_error("Thread creation failed at philos\n"));
		}
	}
	if (!monitoring(data, philos, forks))
		return (0);
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
