/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:31:18 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/20 16:15:40 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(char *str, t_philo *philo)
{
	unsigned int	time;
	
	pthread_mutex_lock(philo->data->message);
	time = get_time() - philo->data->start;
	printf("%u\t%d\t%s\n", time, philo->index, str);
	pthread_mutex_unlock(philo->data->message);
}

int	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*check_state(void *arg)
{
	t_philo	*philo;
	int	i;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philo->data->philos)
		{
			if (philo[i].next_meal < get_time())
			{
				philo->data->dead = 1;
				print_message("died", &philo[i]);
				pthread_mutex_unlock(philo->data->finish);
				return (0);
			}
			if (philo[i].meal_number == philo->data->must_eat)
			{
				philo->data->all_ate++;
				if (philo->data->all_ate == philo->data->philos)
				{
					print_message("all ate", philo);
					pthread_mutex_unlock(philo->data->finish);
					return (0);
				}
			}
			i++;
		}
	}
	return (0);
}

void	*philo_assemble(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		if (philo->data->dead)
			break;
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		print_message("is thinking", philo);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data data;
	t_philo *philo;
	int	i;

	i = 0;	
	if (valid_args(argv, argc) && get_data(argc, argv, &data))
	{
		if (!init_mutexes(&data))
			return (0);
		philo = init_philos(&data);
		data.start = get_time();
		pthread_mutex_lock(data.finish);
		while (i < data.philos)
		{
			if (pthread_create(data.thread + i, NULL, philo_assemble, philo + i) != 0)
				return (print_destroy("Thread creation failed.\n", &data));
			pthread_detach(data.thread[i++]);
			//usleep(100);
		}
		pthread_mutex_lock(data.finish);
		print_destroy(0, &data, philo);
	}
	else
		printf("Error\nInvalid arguments.\n");
	return (1);
}