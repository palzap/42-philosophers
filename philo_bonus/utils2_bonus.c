/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:04:34 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/24 10:11:01 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

unsigned int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*monitoring(void *args)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)args;
	sem_wait(philos->data->reaper);
	i = -1;
	while (++i < philos->data->philos)
		kill(philos->data->pid[i], 1);
	clean_up(philos->data, philos);
	exit (0);
}

void	*banquet_done(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	sem_wait(philo->data->finish);
	clean_up(philo->data, philo);
	exit (0);
}

void	*death(void *args)
{
	t_philo			*philo;
	unsigned int	time;
	int				i;

	i = -1;
	philo = (t_philo *)args;
	while (1)
	{
		time = get_time() - philo->last_meal;
		if (time >= (unsigned int)philo->data->time_to_die)
		{
			sem_wait(philo->can_die);
			print_message(philo->data, philo, 5);
			philo->data->dead = 1;
			pthread_detach(philo->data->death);
			pthread_detach(philo->data->done);
			sem_post(philo->data->reaper);
			while (++i <= philo->data->philos)
				sem_post(philo->data->finish);
		}
	}
	return (0);
}
