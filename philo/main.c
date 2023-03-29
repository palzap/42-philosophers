/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 06:14:47 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/29 18:12:25 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_mutex_t	*forks;
	t_philo			*philo;

	if (argc == 5 || argc == 6)
	{
		if (!valid_args(argv) || !init_data(argc, argv, &data))
			return (0);
		forks = init_forks(&data);
		philo = init_philos(&data, forks);
		data.start = get_time();
		if (!create_threads(&data, philo, forks))
			return (0);
		clean_up(&data, forks, philo);
		return (1);
	}
	else
		print_error("Invalid number of arguments");
	return (0);
}
