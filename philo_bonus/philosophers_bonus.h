/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:15:19 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/23 21:48:56 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

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


# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5
# define DONE 6

typedef struct s_data
{
	int				philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				dead;
	int				all_ate;
	int				*pid;
	pthread_t		death;
	pthread_t		done;
	sem_t			*forks;
	sem_t			*stop;
	sem_t			*reaper;
	sem_t			*finish;
}	t_data;

typedef struct s_philo
{
	int				index;
	int				meal_number;
	unsigned int	last_meal;
	int				start;
	sem_t			*can_die;
	t_data			*data;
}	t_philo;

/*ACTIONS---------------------------------------------------------------------*/

void	*banquet_done(void *args);
void	processes(t_data *data, t_philo *philo);
void	clean_child(t_data *data, t_philo *philos);


/* Prints the respective message based on the value of 'i'. 
Locks "stop" mutex to avoid printing messages at the same time. */
void			print_message(t_data *data, t_philo *philo, int i);

/* Takes the necessary forks to start eating by locking the respective mutex. */
void			take_forks(t_data *data, t_philo *philo);

/* After taking forks (if mutexes are available), locks reaper mutex to prevent
dying while eating.
Uses usleep to for the respective time_to_eat, unlocks mutexes in the end. */
void			eating(t_data *data, t_philo *philo);

/* After eating, simply uses usleep for the respective time_to_sleep. */
void			sleeping(t_data *data, t_philo *philo);

/*FREE------------------------------------------------------------------------*/

/* Prints the error message "str" to the standard error. */
int				print_error(char *str);

/* Destroys mutexes and frees all allocated memory. */
void			clean_up(t_data *data, t_philo *philos);

/*INIT------------------------------------------------------------------------*/

/* Initializes all philosophers with data. */
t_philo			*init_philos(t_data *data);

/* Initializes data struct with the correct information. */
int				init_data(int argc, char **argv, t_data *data);

/* Checks if the arguments are valid. */
int				valid_args(char **argv);

void			init_semaphore(t_data *data);

/* Allocates memory for all fork mutexes. */
//pthread_mutex_t	*init_forks(t_data *data);

/*THREADS---------------------------------------------------------------------*/

/* Monitoring thread that runs in parallel to the philo threads.
Constantly checks if any philosopher died or if all philosophers ate the
number of times pointed to by must_eat. */
void			*monitoring(void *args);

/* Creates the monitoring thread. */
/* int				monitoring(t_data *data, t_philo *philos); */

/* Simple function that executes eating, sleeping and thinking. */
void			actions(t_data *data, t_philo *philo);

/* Function that runs on every philo thread. It checks availability of mutexes 
and calls the "actions" function to execute all requested actions. */
void			*assemble(void *args);

/* Creates all philo threads. */
int				create_threads(t_data *data, t_philo *philos);

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

/*UTILS2----------------------------------------------------------------------*/

/* Calculates the current time in miliseconds after. */
unsigned int	get_time(void);

/* Checks if any philosopher died. */
void			*death(void *args);

#endif