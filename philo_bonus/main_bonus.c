/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:46:06 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/30 09:09:02 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int ac, char **av)
{
	t_data	*data;
	pthread_t	monitor;
	pthread_t	banquet;
	int	i;

	i = 0;
	if (ac == 5 || ac == 6)
	{
		data = init_data(ac, av);
		data->start = get_time();
		data->index = -1;
		while (++data->index < data->philo_no)
		{
			data->pid[data->index] = fork();
			if(data->pid[data->index] == 0)
			{
				processes(data);
				break;
			}
		}
		pthread_create(&monitor, 0, monitoring, data);
		pthread_create(&banquet, 0, banquet_done, data);
		pthread_join(monitor, 0);
		pthread_join(banquet, 0);
		waitpid(-1, 0, WNOHANG);
		clean_exit(data);
		return (0);
	}
	return (0);
}