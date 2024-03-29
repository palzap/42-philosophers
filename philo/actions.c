/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:02:25 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/30 08:08:59 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_philo *philo, int i)
{
	unsigned int	time;

	if (philo->data->dead)
		return ;
	time = get_time() - philo->data->start;
	pthread_mutex_lock(&philo->data->stop);
	if (i == 1)
		printf("%u %d %s", time, philo->index, "has taken a fork\n");
	if (i == 2)
		printf("%u %d %s", time, philo->index, "is eating\n");
	if (i == 3)
		printf("%u %d %s", time, philo->index, "is sleeping\n");
	if (i == 4)
		printf("%u %d %s", time, philo->index, "is thinking\n");
	if (i == 5)
		printf("%u %d %s", time, philo->index, "died\n");
	pthread_mutex_unlock(&philo->data->stop);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, 1);
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, 1);
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->reaper);
	print_message(philo, 2);
	philo->last_meal = get_time();
	philo->meal_number++;
	if (philo->meal_number == philo->data->must_eat)
		philo->data->all_ate--;
	pthread_mutex_unlock(&philo->reaper);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	print_message(philo, 3);
	usleep(philo->data->time_to_sleep * 1000);
}
