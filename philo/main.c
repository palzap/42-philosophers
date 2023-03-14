/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:31:18 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/14 14:54:41 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*start_dinner(void *arg)
{
	t_philo *philo;

	philo = arg;
	philo->dead
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		pthread_mutex_init(data->forks + i, NULL);
		i++;
	}	
}

t_philo	*init_philos(t_data *data)
{
	t_philo *philo;
	int	i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->philos);
	while (i < data->philos)
	{
		philo[i].index = i;
		philo[i].meal_time = 0;
		philo[i].next_meal = 0;
		philo[i].meal_number = 0;
		philo[i].dead = 0;
		philo[i].right_fork = i;
		philo[i].left_fork = (i + (data->philos - 1) % data->philos);
		i++;
	}
	return (philo);
}

void	get_data(int argc, char **argv, t_data *data)
{
	data->philos = ft_atoi(argv[1]);
	data->thread = malloc(sizeof(pthread_t) * data->philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos);
	data->die = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	else 
		data->max_eat = INT_MAX;
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

int	main(int argc, char **argv)
{
	t_data *data;
	t_philo *philo;
	int	i;

	i = 0;	
	data = malloc(sizeof(t_data));
	if (argc == 5 || argc == 6)
	{
		if (!valid_args(argv))
		{
			printf("Error\nInvalid argument.\n");
			return (0);
		}
		get_data(argc, argv, data);
		philo = init_philos(data);
		init_forks(data);
		while (i < data->philos)
		{
			pthread_create(data->thread + i, NULL, start_dinner, philo + i);

		}
	}
	else
		printf("Error\nIncorrect number of arguments.\n");
	return (0);
}