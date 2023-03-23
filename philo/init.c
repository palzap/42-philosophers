/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:00:21 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/22 15:12:10 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*init_philos(t_data *data, pthread_mutex_t *forks)
{
	t_philo	*philos;
	int		i;

	philos = malloc(data->philos * sizeof(t_philo));
	if (!philos)
	{
		clean_up(data, forks, 0);
		print_error("Memory allocation failed at philos\n");
	}
	i = -1;
	while (++i < data->philos)
	{
		philos[i].index = i + 1;
		philos[i].meal_number = 0;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % data->philos];
		philos[i].last_meal = get_time();
		if (pthread_mutex_init(&philos[i].reaper, NULL) != 0)
		{
			clean_up(data, forks, 0);
			print_error("Mutex init failed at philos.reaper\n");
		}
		philos[i].data = data;
	}
	return (philos);
}

int	init_data(int argc, char **argv, t_data *data)
{
	data->philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	if (data->philos == 0 || data->must_eat == 0)
		return (print_error("Number of philosophers must be > 0\n"));
	if (pthread_mutex_init(&data->stop, NULL) != 0)
		return (print_error("Mutex init failed at data->stop\n"));
	data->all_ate = 0;
	data->dead = 0;
	return (1);
}

int	valid_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
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

pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(data->philos * sizeof(pthread_mutex_t));
	if (!forks)
		print_error("Memory allocation failed at forks\n");
	i = 0;
	while (i < data->philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			print_error("Mutex init failed at forks\n");
		i++;
	}
	return (forks);
}
