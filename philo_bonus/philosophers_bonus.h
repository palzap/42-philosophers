/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:00:37 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/30 10:38:05 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHERS_BONUS_H
# define PHILOSPHERS_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_philo
{
	int				id;
	int				meal_number;
	int				is_dead;
	unsigned int	last_meal;
	sem_t			can_die;
}	t_philo;

typedef struct s_data
{
	int				philo_no;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	t_philo			*philos;
	int				*pid;
	int				all_ate;
	int				start;
	int				index;
	sem_t			*forks;
	sem_t			*message;
	sem_t			*finish;
	sem_t			*meals;
	sem_t			*is_dead;
}	t_data;

/*ACTIONS---------------------------------------------------------------------*/

/* Prints the respective message based on the value of 'i'. 
Locks "stop" mutex to avoid printing messages at the same time. */
void			print_message(t_data *data, int i);

/* Takes the necessary forks to start eating by locking the respective mutex. */
void			take_forks(t_data *data);

/* After taking forks (if mutexes are available), locks reaper mutex to prevent
dying while eating.
Uses usleep to for the respective time_to_eat, unlocks mutexes in the end. */
void			eating(t_data *data);

/* After eating, simply uses usleep for the respective time_to_sleep. */
void			sleeping(t_data *data);

/*FREE------------------------------------------------------------------------*/

/* Prints the error message "str" to the standard error. */
//int				print_error(char *str);

void			*monitoring(void *arg);
void			*banquet_done(void *arg);
void			clean_exit(t_data *data);


/*INIT------------------------------------------------------------------------*/

void			init_semaphores(t_data *data);
void			init_philos(t_data *data);
t_data			*init_data(int ac, char **av);

/*PROCESSES-------------------------------------------------------------------*/

unsigned int	get_time(void);
void			*death_check(void *arg);
void			processes(t_data *data);

/*UTILS-----------------------------------------------------------------------*/

/* Prints 'c' to the file descriptor fd. */
void			ft_putchar_fd(char c, int fd);

/* Prints "str" to the file descriptor fd. */
void			ft_putstr_fd(char *str, int fd);

/* Checks if 'c' is a space. man isspace. */
int				ft_isspace(int c);

/* Checks if 'c' is a digit. man isdigit. */
int				ft_isdigit(int c);

/* Converts "str" to an int. man atoi. */
int				ft_atoi(const char *str);

#endif