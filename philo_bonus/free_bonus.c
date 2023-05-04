/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:46:41 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/04 15:09:16 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	create_monitor_threads(t_data *data)
{
	pthread_t	monitor;
	pthread_t	banquet;

	pthread_create(&monitor, 0, monitoring, data);
	pthread_create(&banquet, 0, banquet_done, data);
	pthread_join(monitor, 0);
	pthread_join(banquet, 0);
	return (0);
}

void	*monitoring(void *arg)
{
	t_data	*data;
	int		i;

	i = -1;
	data = (t_data *)arg;
	sem_wait(data->finish);
	while (++i < data->philo_no)
		sem_post(data->meals);
	return (0);
}

void	*banquet_done(void *arg)
{
	t_data	*data;
	int		i;
	int		j;

	i = -1;
	j = 0;
	data = (t_data *)arg;
	while (1)
	{
		sem_wait(data->meals);
			data->all_ate--;
		if (data->all_ate == 0)
		{
			sem_post(data->finish);
			while (++i < data->philo_no)
				kill(data->pid[i], SIGKILL);
			return (0);
		}
	}
	return (0);
}

void	clean_exit(t_data *data)
{
	int		i;
	char	*philo;

	i = -1;
	sem_close(data->forks);
	sem_close(data->finish);
	sem_close(data->meals);
	sem_close(data->message);
	sem_close(data->dead);
	sem_unlink("forks");
	sem_unlink("finish");
	sem_unlink("meals");
	sem_unlink("message");
	sem_unlink("dead");
	while (++i < data->philo_no)
	{
		philo = ft_itoa(data->philos[i].id);
		sem_close(data->philos[i].can_die);
		sem_unlink(philo);
		free(philo);
	}
	free(data->philos);
	free(data->pid);
	free(data);
}
