/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:15:19 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/21 13:54:14 by pealexan         ###   ########.fr       */
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

# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5
# define DONE 6

typedef struct s_data
{
	int philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
	int	dead;
	int	all_ate;
	pthread_mutex_t	stop;
}	t_data;

typedef	struct s_philo
{
	pthread_t	id;
	int	index;
	int	meal_number;
	unsigned int	last_meal;
	int	start;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	reaper;
	t_data	*data;
}	t_philo;

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
int	ft_isspace(int c);
int	ft_isdigit(int c);
int	ft_atoi(const char *str);
int	print_error(char *str);
int	init_data(int argc, char **argv, t_data *data);
int	valid_args(char **argv);
pthread_mutex_t	*init_forks(t_data *data);
void	clean_up(t_data *data, pthread_mutex_t *forks, t_philo *philos);
unsigned int	get_time(void);
t_philo	*init_philos(t_data *data, pthread_mutex_t *forks);
int	banquet_done(t_philo *philo);
int	death(t_philo *philo);
void	*monitor(void *args);
int	monitoring(t_data *data, t_philo *philos, pthread_mutex_t *forks);
void	print_message(t_philo *philo, int i);
void	take_forks(t_philo *philo);
void	eating(t_philo *philo);
void    sleeping(t_philo *philo);
void	*assemble(void *args);
int	create_threads(t_data *data, t_philo *philos, pthread_mutex_t *forks);
void	actions(t_philo *philo);

#endif