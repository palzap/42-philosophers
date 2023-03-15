/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:31:18 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/15 11:27:33 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->death);
	philo->last_meal = get_time();
	usleep(philo->data->time_to_eat);
	print_message();
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	philo->meal_number++;
}

void	philo_assemble(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->data->start = 
	eating(philo);
	sleeping(philo);
	thinking(philo);
}

int	print_destroy(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return (print_clean_data(str, data));
}

int	print_clean_data(char *str, t_data *data)
{
	if (data->thread)
		free(data->thread);
	if (data->forks)
		free(data->forks);
	if (data)
		free(data);
	return (print_error(str));
}

int	print_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
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
		return (print_destroy("Memory allocation failed at philo\n", data));
	while (i < data->philos)
	{
		philo[i].index = i;
		philo[i].last_meal = 0;
		philo[i].next_meal = 0;
		philo[i].meal_number = 0;
		philo[i].is_dead = 0;
		pthread_mutex_init(&philo[i].death, NULL);
		philo[i].right_fork = &data->forks[i];
		philo[i].left_fork = &data->forks[(i - 1) % data->philos];
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
		return (print_error("Memory allocation failed at data->forks\n"));
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

int	main(int argc, char **argv)
{
	t_data *data;
	t_philo *philo;
	int	i;

	i = 0;	
	data = malloc(sizeof(t_data));
	if (!data)
		return (print_error("Memory allocation failed at data\n"));
	if (valid_args(argv, argc) && get_data(argc, argv, data))
	{
		if (!init_forks(data))
			return (0);
		philo = init_philos(data);
		if (!philo)
			return(0);
		while (!data->dead)
		{
			pthread_create(&data->thread[i], NULL, philo_assemble, &philo[i]);
			
		}
	}
	else
		printf("Error\nInvalid arguments.\n");
	return (1);
}