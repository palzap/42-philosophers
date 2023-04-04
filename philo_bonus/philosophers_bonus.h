/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:00:37 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/04 09:21:03 by pealexan         ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				meal_number;
	int				is_dead;
	unsigned int	last_meal;
	sem_t			*can_die;
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
	sem_t			*dead;
	sem_t			*forks;
	sem_t			*message;
	sem_t			*finish;
	sem_t			*meals;
	sem_t			*is_dead;
}	t_data;

/*ACTIONS---------------------------------------------------------------------*/

/* Prints the respective message based on the value of 'i'. 
Locks "message" semaphore to avoid printing messages at the same time. */
void			print_message(t_data *data, int i);

/* Takes forks to start eating by locking the respective semaphore. 
Usleep is used to prevent philosophers from taking forks right away.*/
void			take_forks(t_data *data);

/* After taking forks (if semaphore is available), locks reaper semaphore to 
prevent dying while eating.
Uses usleep for the respective time_to_eat, unlocks semaphores in the end. */
void			eating(t_data *data);

/* After eating, simply uses usleep for the respective time_to_sleep. */
void			sleeping(t_data *data);

/*FREE------------------------------------------------------------------------*/

/* Creates and joins the monitoring threads. */
int				create_monitor_threads(t_data *data);

/* Waits for finish semaphore to be available to pass information to 
banquet_done to terminate all processes. */
void			*monitoring(void *arg);

/* Waits for semaphores meals and finish to kill all processes, clean and 
exit program. */
void			*banquet_done(void *arg);

/* Destroys all semaphores and frees all allocated memory. */
void			clean_exit(t_data *data);

/*INIT------------------------------------------------------------------------*/

/* Creates all semaphores. */
void			init_semaphores(t_data *data);

/* Initializes all philosophers. */
void			init_philos(t_data *data);

/* Initializes all needed data. */
t_data			*init_data(int ac, char **av);

/*PROCESSES-------------------------------------------------------------------*/

/* Calculates the current time in miliseconds after. */
unsigned int	get_time(void);

/* Checks condition of current philosopher. If dead, post finish semaphore. */
void			*death_check(void *arg);

/* Process of each philosopher. */
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

/* Converts "n" to a string. man itoa. */
char			*ft_itoa(int n);

#endif