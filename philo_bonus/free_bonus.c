/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:46:41 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/30 09:17:45 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*monitoring(void *arg)
{
	t_data	*data;
	int		i;
	
	i = -1;
	data = (t_data *)arg;
	sem_wait(data->finish);
	while(++i < data->philo_no)
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
	int	i;

	i = -1;
	sem_close(data->forks);
	sem_close(data->finish);
	sem_close(data->meals);
	sem_close(data->message);
	sem_unlink("forks");
	sem_unlink("finish");
	sem_unlink("meals");
	sem_unlink("message");
	while (++i < data->philo_no)
		sem_destroy(&data->philos->can_die);
	free(data->philos);
	free(data->pid);
	free(data);
}