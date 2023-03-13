/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:15:19 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/13 11:47:58 by pealexan         ###   ########.fr       */
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

typedef struct s_data
{
	int philos;
	int	die;
	int	eat;
	int	sleep;
	int	max_eat;
}	t_data;

typedef	struct philo
{
	//t_data	*data;
	int	index;
	int	meal_time;
	int	next_meal;
	int	meal_no;
	int	is_dead;
}	t_philo;


/*UTILS-----------------------------------------------------------------------*/

/* Converts *str to int. man atoi.  */
int	ft_atoi(const char *str);

/* Checks if 'c' is a digit. man isdigit */
int	ft_isdigit(int c);

/* Checks if 'c' is a space. man isspace */
int	ft_isspace(int c);


#endif