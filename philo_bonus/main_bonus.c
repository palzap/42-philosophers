/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 06:14:47 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/24 09:57:24 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philos;
	pthread_t		monitor;
	int	i;
	
	i = -1;
	if (argc == 5 || argc == 6)
	{
		if (!valid_args(argv) || !init_data(argc, argv, &data))
			return (0);
		philos = init_philos(&data);
		init_semaphore(&data);
		data.start = get_time();
		philos->id = -1;
		while (++philos->id < data.philos)
		{
			usleep(100);
			data.pid[philos->id] = fork();
			if (data.pid[philos->id] == 0)
				processes(&data, philos);
		}
		pthread_create(&monitor, 0, monitoring, philos);
		pthread_detach(monitor);
		i = -1;
		while (++i < data.philos)
			waitpid(data.pid[i], NULL, 0);
		clean_up(&data, philos);
		exit (0);
	}
	else
		print_error("Invalid number of arguments");
	return (0);
}
