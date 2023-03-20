/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:55:14 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/20 16:17:04 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_destroy(char *str, t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(data->message);
	pthread_mutex_destroy(data->finish);
	while (i < data->philos)
	{
		pthread_mutex_destroy(data->forks + i);
		pthread_mutex_destroy(data->eatings + i);
		i++;
	}
	free(philo);
	free(data->message);
	free(data->finish);
	free(data->forks);
	free(data->eatings);
	free(data->thread);
	return (print_clean_data(str, data));
}

int	print_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	return (0);
}