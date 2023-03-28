/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_philo.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:00:37 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/28 16:11:44 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_PHILO_H
# define NEW_PHILO_H

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
	int				dead;
	int				all_ate;
	int				start;
	int				index;
	//pthread_t		death;
	//pthread_t		done;
	sem_t			*forks;
	sem_t			*message;
	//sem_t			*reaper;
	sem_t			*finish;
	sem_t			*meals;
}	t_data;


t_data			*init_data(int ac, char **av);
void			init_philos(t_data *data);
void			init_semaphores(t_data *data);
void			clean_exit(t_data *data);
void			print_message(t_data *data, int n, int i);
void			take_forks(t_data *data, int n);
void			eating(t_data *data, int n);
void			sleeping(t_data *data, int n);
void			actions(t_data *data, int n);
void			processes(t_data *data, int i);
unsigned int	get_time(void);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *str, int fd);
int				ft_isspace(int c);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);

#endif