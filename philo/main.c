/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:31:18 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/13 14:02:43 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_data(int argc, char **argv, t_data *data)
{
	data->philos = ft_atoi(argv[1]);
	data->die = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	else 
		data->max_eat = 0;
	return ;
} 

int	valid_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data data;
	t_philo *philo;
	
	if (argc == 5 || argc == 6)
	{
		if (!valid_args(argv))
		{
			printf("Error\nInvalid argument.\n");
			return (0);
		}
		get_data(argc, argv, &data);
	}
	else
		printf("Error\nIncorrect number of arguments.\n");
	return (0);
}