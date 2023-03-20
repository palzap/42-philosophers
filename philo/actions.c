/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:07:03 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/20 16:07:33 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_message("has taken a fork", philo);
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_message("has taken a fork", philo);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eatings[philo->index]);
	philo->next_meal = get_time() + philo->data->time_to_die;
	print_message("is eating", philo);
	if (philo->data->must_eat >= 0)
		philo->meal_number++;
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->eatings[philo->index]);
}

void	sleeping(t_philo *philo)
{
	print_message("is sleeping", philo);
	usleep(philo->data->time_to_sleep);
}