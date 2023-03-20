/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:15:19 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/20 15:39:10 by pealexan         ###   ########.fr       */
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
	pthread_t	*thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eatings;
	pthread_mutex_t	*message;
	pthread_mutex_t	*finish;
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
	int	left_fork;
	int	right_fork;
	t_data	*data;
}	t_philo;

void	print_message(char *str, t_philo *philo);
int		get_time(void);
void	take_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	*check_state(void *arg);
void	*philo_assemble(void *arg);
int		init_forks(t_data *data);
t_philo	*init_philos(t_data *data);
int		get_data(int argc, char **argv, t_data *data);
int		valid_args(char **argv, int argc);


/*DESTROY---------------------------------------------------------------------*/

/* Destroys all mutexes mutexes, calls print_clean_data. */
int		print_destroy(char *str, t_data *data);

/* Frees all allocated memory for data, calls print_error. */
int		print_clean_data(char *str, t_data *data);

/* Prints the error message "str" in STD_ERR. */
int		print_error(char *str);


/*UTILS-----------------------------------------------------------------------*/

/* Prints 'c' to the file descriptor. */
void	ft_putchar_fd(char c, int fd);

/* Prints "str" to the file descriptor. */
void	ft_putstr_fd(char *str, int fd);

/* Converts *str to int. man atoi.  */
int		ft_atoi(const char *str);

/* Checks if 'c' is a digit. man isdigit */
int		ft_isdigit(int c);

/* Checks if 'c' is a space. man isspace */
int		ft_isspace(int c);

#endif