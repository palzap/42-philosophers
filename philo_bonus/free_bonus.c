/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:03:41 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/23 21:49:31 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	print_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit (0);
}

void	clean_up(t_data *data, t_philo *philos)
{
	sem_close(data->forks);
	sem_close(data->finish);
	sem_close(data->reaper);
	sem_close(data->stop);
	sem_close(philos->can_die);
	sem_unlink("forks");
	sem_unlink("finish");
	sem_unlink("reaper");
	sem_unlink("stop");
	sem_unlink("can_die");
	if (philos)
	{
		//free(philos);
		philos = 0;
	}
}
