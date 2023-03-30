/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:01:17 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/30 08:05:37 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	while (1)
	{
		if (death(philos))
			return (0);
		if (!philos->data->all_ate)
			return (0);
	}
	return (0);
}

void	*assemble(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->index % 2)
		usleep(500);
	while (1)
	{
		if (philo->data->philos == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			print_message(philo, 1);
			return (0);
		}
		if (philo->data->dead || !philo->data->all_ate)
			return (0);
		eating(philo);
		if (philo->data->dead || !philo->data->all_ate)
			return (0);
		sleeping(philo);
		if (philo->data->dead || !philo->data->all_ate)
			return (0);
		print_message(philo, 4);
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
	if (pthread_join(monitoring, 0) != 0)
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
		if (pthread_create(&philos[i].id, NULL,
				assemble, (void *)&philos[i]) != 0)
		{
			clean_up(data, forks, philos);
			return (print_error("Thread creation failed at philos\n"));
		}
	}
	return (1);
}

int	join_threads(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < data->philos)
	{
		if (pthread_join(philos[i].id, 0) != 0)
		{
			clean_up(data, forks, philos);
			return (print_error("Thread join failed at philos\n"));
		}
	}
	return (1);
}
