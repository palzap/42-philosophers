/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:03:41 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/29 19:25:09 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

void	clean_up(t_data *data, pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	pthread_mutex_destroy(&data->stop);
	if (forks)
	{
		i = 0;
		while (i < data->philos)
		{
			pthread_mutex_destroy(&philos[i].reaper);
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
		free(forks);
	}
	if (philos)
		free(philos);
}
