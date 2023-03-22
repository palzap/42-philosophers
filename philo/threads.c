/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:01:17 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/22 09:15:54 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	if (philos->data->must_eat > 0)
	{
		while (philos->data->must_eat > philos->meal_number
			&& !philos->data->dead)
		{
			if (death(philos))
				break ;
		}
	}
	else
	{
		while (!philos->data->dead)
		{
			if (death(philos))
				break ;
		}
	}
	return (0);
}

void	actions(t_philo *philo)
{
	eating(philo);
	if (philo->data->must_eat != philo->meal_number)
	{
		sleeping(philo);
		print_message(philo, 4);
	}
}

void	*assemble(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->data->philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, 1);
		return (0);
	}
	if (philo->data->must_eat > 0)
	{
		while (philo->data->must_eat > philo->meal_number && !philo->data->dead)
			actions(philo);
	}
	else
	{
		while (!philo->data->dead)
			actions(philo);
	}
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

int	create_threads(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < data->philos)
	{
		philos[i].start = get_time();
		if (pthread_create(&philos[i].id, NULL,
				assemble, (void *)&philos[i]) != 0)
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
