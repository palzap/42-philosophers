/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:47:55 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/30 10:42:53 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	init_semaphores(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("meals");
	sem_unlink("message");
	sem_unlink("finish");
	data->forks = sem_open("forks", O_CREAT, 0644, data->philo_no);
	data->meals = sem_open("meals", O_CREAT, 0644, 0);
	data->message = sem_open("message", O_CREAT, 0644, 1);
	data->finish = sem_open("finish", O_CREAT, 0644, 0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_no)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meal_number = 0;
		data->philos[i].last_meal = get_time();
		sem_init(&data->philos[i].can_die, 0, 1);
	}
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->philos = (t_philo *)malloc(sizeof(t_philo) * (ft_atoi(av[1])));
	data->pid = (int *)malloc(sizeof(int) * (ft_atoi(av[1])));
	if (!data || !data->philos || !data->pid)
	{
		ft_putstr_fd("Error\nMemory allocation failed.\n", 2);
		exit (1);
	}
	data->philo_no = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->must_eat = -1;
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	data->all_ate = ft_atoi(av[1]);
	data->start = 0;
	data->index = 0;
	init_philos(data);
	init_semaphores(data);
	return (data);
}