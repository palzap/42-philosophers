/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 06:14:47 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/23 21:51:04 by pealexan         ###   ########.fr       */
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
		while (++i < data.philos)
		{
			usleep(60);
			philos[i].start = get_time();
			data.pid[i] = fork();
			if (data.pid[i] == 0)
				processes(&data, &philos[i]);
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
