/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:02:25 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/23 21:49:15 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_message(t_data *data, t_philo *philo, int i)
{
	unsigned int	time;

	if (philo->data->dead)
		return ;
	time = get_time() - philo->start;
	sem_wait(data->stop);
	if (i == 1)
		printf("%u\t%d\t%s", time, philo->index, "has taken a fork\n");
	if (i == 2)
		printf("%u\t%d\t%s", time, philo->index, "is eating\n");
	if (i == 3)
		printf("%u\t%d\t%s", time, philo->index, "is sleeping\n");
	if (i == 4)
		printf("%u\t%d\t%s", time, philo->index, "is thinking\n");
	if (i == 5)
		printf("%u\t%d\t%s", time, philo->index, "has died\n");
	sem_post(data->stop);
}

void	take_forks(t_data *data, t_philo *philo)
{
	sem_wait(data->forks);
	print_message(data, philo, 1);
	sem_wait(data->forks);
	print_message(data, philo, 1);
}

void	eating(t_data *data, t_philo *philo)
{
	take_forks(data, philo);
	print_message(data, philo, 2);
	philo->last_meal = get_time();
	sem_post(philo->can_die);
	usleep(philo->data->time_to_eat * 1000);
	sem_post(data->forks);
	sem_post(data->forks);
	philo->meal_number++;
}

void	sleeping(t_data *data, t_philo *philo)
{
	print_message(data, philo, 3);
	usleep(philo->data->time_to_sleep * 1000);
}
