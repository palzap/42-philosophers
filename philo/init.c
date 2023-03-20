/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:08:26 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/20 16:08:55 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(data->finish, NULL) != 0)
		return (print_clean_data("Mutex init failed\n", data));
	if (pthread_mutex_init(data->message, NULL) != 0)
		return (print_clean_data("Mutex init failed\n", data));
	while (i < data->philos)
	{
		if (pthread_mutex_init(data->forks + i, NULL) != 0)
			return (print_clean_data("Mutex init failed\n", data));
		if (pthread_mutex_init(data->eatings + i, NULL) != 0)
			return (print_clean_data("Mutex init failed\n", data));
		i++;
	}
	return (1);	
}

t_philo	*init_philos(t_data *data)
{
	t_philo *philo;
	int	i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->philos);
	if (!philo)
	{
		print_destroy("Memory allocation failed at philo\n", data);
		return (0);
	}
	while (i < data->philos)
	{
		philo[i].index = i;
		philo[i].last_meal = 0;
		philo[i].next_meal = data->time_to_die;
		philo[i].meal_number = 0;
 		philo[i].right_fork = i;
		philo[i].left_fork = (i - 1) % data->philos;
		philo[i].data = data;
		i++;
	}
	return (philo);
}

int	get_data(int argc, char **argv, t_data *data)
{
	data->philos = ft_atoi(argv[1]);
	data->thread = malloc(sizeof(pthread_t) * data->philos);
	if (!data->thread)
		return (print_error("Memory allocation failed at data->thread\n"));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos);
	if (!data->forks)
		return (print_error("Memory allocation failed at data->forks\n"));
	data->eatings = malloc(sizeof(pthread_mutex_t) * data->philos);
	if (!data->eatings)
		return (print_error("Memory allocation failed at data->eatings\n"));
	data->finish = malloc(sizeof(pthread_mutex_t));
	data->message = malloc(sizeof(pthread_mutex_t));
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	data->start = 0;
	data->dead = 0;
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	return (1);
}

int	valid_args(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (argv[i])
		{
			j = 0;
			while (argv[i][j])
			{
				if (!ft_isdigit(argv[i][j]))
					return (0);
				j++;
			}
			i++;
		}
		return (1);
	}
	return (0);
}