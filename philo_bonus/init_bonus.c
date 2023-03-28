/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:00:21 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/28 15:13:29 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	init_semaphore(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("reaper");
	sem_unlink("stop");
	sem_unlink("finish");
	data->forks = sem_open("forks", O_CREAT, 0644, data->philos);
	printf("%d\n", data->forks);
	data->reaper = sem_open("reaper", O_CREAT, 0644, 0);
	data->stop = sem_open("stop", O_CREAT, 0644, 1);
	data->finish = sem_open("finish", O_CREAT, 0644, 0);
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(data->philos * sizeof(t_philo));
	if (!philos)
	{
		clean_up(data, philos);
		print_error("Memory allocation failed at philos\n");
	}
	i = -1;
	while (++i < data->philos)
	{
		philos[i].index = i + 1;
		philos[i].meal_number = 0;
		philos[i].last_meal = get_time();
		sem_unlink("can_die");
		philos[i].can_die = sem_open("can_die", O_CREAT, 0644, 0);
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
	data->pid = malloc(sizeof(int *) * data->philos);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	if (data->philos == 0 || data->must_eat == 0)
		return (print_error("Number of philosophers/must_eat must be > 0\n"));
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
