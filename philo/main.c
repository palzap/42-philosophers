/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:31:18 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/20 08:28:46 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(char *str, t_philo *philo)
{
	int	time;
	
	time = get_time() - philo->data->start;
	printf("%d %d %s\n", time, philo->index, str);
}

int	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	print_message("has taken a fork", philo);
	pthread_mutex_lock(&philo->left_fork);
	print_message("has taken a fork", philo);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->reaper);
	philo->last_meal = get_time();
	philo->next_meal = get_time() + philo->data->time_to_die;
	usleep(philo->data->time_to_eat);
	print_message("is eating", philo);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	philo->meal_number++;
}

void	sleeping(t_philo *philo)
{
	
}

void	thinking(t_philo *philo)

void	philo_assemble(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	take_forks(philo);
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
		pthread_mutex_destroy(&data->reapers[i]);
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
	if (data->reapers)
		free(data->reapers);
	if (data)
		free(data);
	if (!str)
		return (0);
	else
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
		if (pthread_mutex_init(&data->reapers[i], NULL) != 0)
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
		philo[i].reaper = &data->reapers[i];
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
	if (!data->forks)
		return (print_error("Memory allocation failed at data->forks\n"));
	data->reapers = malloc(sizeof(pthread_mutex_t) * data->philos);
	if (!data->reapers)
		return (print_error("Memory allocation failed at data->reapers\n"));
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
			data->start = get_time();
			pthread_create(&data->thread[i], NULL, philo_assemble, &philo[i]);
			
		}
	}
	else
		printf("Error\nInvalid arguments.\n");
	return (1);
}