/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:15:19 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/20 07:59:11 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data
{
	pthread_t			*thread;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*reapers;
	int philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
	int	start;
	int	dead;
	int	all_ate;
}	t_data;

typedef	struct s_philo
{
	int	index;
	int	last_meal;
	int	next_meal;
	int	meal_number;
	int	is_dead;
	pthread_mutex_t	*reaper;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data	*data;
}	t_philo;


/*UTILS-----------------------------------------------------------------------*/

/* Prints 'c' to the file descriptor. */
void	ft_putchar_fd(char c, int fd);

/* Prints "str" to the file descriptor. */
void	ft_putstr_fd(char *str, int fd);

/* Converts *str to int. man atoi.  */
int	ft_atoi(const char *str);

/* Checks if 'c' is a digit. man isdigit */
int	ft_isdigit(int c);

/* Checks if 'c' is a space. man isspace */
int	ft_isspace(int c);

#endif