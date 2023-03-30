/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:46:06 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/30 11:20:44 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int ac, char **av)
{
	t_data		*data;
	int			i;

	i = 0;
	if (ac == 5 || ac == 6)
	{
		data = init_data(ac, av);
		data->index = -1;
		while (++data->index < data->philo_no)
		{
			data->pid[data->index] = fork();
			if (data->pid[data->index] == 0)
			{
				processes(data);
				break ;
			}
		}
		create_monitor_threads(data);
		waitpid(-1, 0, WNOHANG);
		clean_exit(data);
		return (0);
	}
	else
		ft_putstr_fd("Invalid number of arguments", 2);
	return (0);
}
