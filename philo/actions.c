/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:02:25 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/21 14:17:32 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_philo *philo, int i)
{
	unsigned int time;

	if (philo->data->dead)
		return ;
	time = get_time() - philo->start;
	pthread_mutex_lock(&philo->data->stop);
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
	pthread_mutex_unlock(&philo->data->stop);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, 1);
	print_message(philo, 1);
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->reaper);
	print_message(philo, 2);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->reaper);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->meal_number++;
}

void    sleeping(t_philo *philo)
{
    print_message(philo, 3);
	usleep(philo->data->time_to_sleep * 1000);
}