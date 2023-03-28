/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:00:20 by pealexan          #+#    #+#             */
/*   Updated: 2023/03/28 16:20:47 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_philo.h"

unsigned int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
	{
		ft_putchar_fd(*str, fd);
		str++;
	}
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(((int)*str)))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

void	init_semaphores(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("meals");
	sem_unlink("message");
	sem_unlink("finish");
	data->forks = sem_open("forks", O_CREAT, 0644, data->philo_no);
	data->meals = sem_open("meals", O_CREAT, 0644, 0);
	data->message = sem_open("message", O_CREAT, 0644, 1);
	data->finish = sem_open("finish", O_CREAT, 0644, 0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_no)
	{
		data->philos[i].id = i + 1;
		data->philos[i].can_die = 0;
		data->philos[i].meal_number = 0;
		data->philos[i].last_meal = 0;
	}
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->philos = (t_philo *)malloc(sizeof(t_philo) * (ft_atoi(av[1])));
	data->pid = (int *)malloc(sizeof(int) * (ft_atoi(av[1])));
	if (!data || !data->philos || !data->pid)
	{
		ft_putstr_fd("Error\nMemory allocation failed.\n", 2);
		exit (1);
	}
	data->philo_no = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->must_eat = -1;
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	data->dead = 0;
	data->all_ate = 0;
	data->start = 0;
	data->index = 0;
	init_philos(data);
	init_semaphores(data);
	return (data);
}

void	print_message(t_data *data, int n, int i)
{
	unsigned int	time;

	time = get_time() - data->start;
	sem_wait(data->message);
	if (i == 1)
		printf("%u %d %s", time, data->philos[n].id, "has taken a fork\n");
	if (i == 2)
		printf("%u %d %s", time, data->philos[n].id, "is eating\n");
	if (i == 3)
		printf("%u %d %s", time, data->philos[n].id, "is sleeping\n");
	if (i == 4)
		printf("%u %d %s", time, data->philos[n].id, "is thinking\n");
	if (i == 5)
		printf("%u %d %s", time, data->philos[n].id, "has died\n");
	sem_post(data->message);
}

void	take_forks(t_data *data, int n)
{
	sem_wait(data->forks);
	print_message(data, n, 1);
	sem_wait(data->forks);
	print_message(data, n, 1);
}

void	eating(t_data *data, int n)
{
	take_forks(data, n);
	print_message(data, n, 2);
	data->philos[n].last_meal = get_time();
	//sem_post(philo->can_die);
	usleep(data->time_to_eat * 1000);
	sem_post(data->forks);
	sem_post(data->forks);
	data->philos[n].meal_number++;
	if (data->philos[n].meal_number == data->must_eat)
		sem_post(data->meals);
}

void	sleeping(t_data *data, int n)
{
	print_message(data, n, 3);
	usleep(data->time_to_sleep * 1000);
}

void	actions(t_data *data, int n)
{
	eating(data, n);
	sleeping(data, n);
	print_message(data, n, 4);
}

void	*death_check(void *arg)
{
	unsigned int	time;
	t_data			*data;

	data = (t_data *)arg;	
	while (1)
	{
		time = get_time() - data->philos[data->index].last_meal;
		if (time > (unsigned int)data->time_to_die)
		{
			sem_post(data->finish);
			print_message(data, data->index, 5);
			break ;
		}
	}
	return (0);
}

void	processes(t_data *data, int i)
{
	int	n;
	pthread_t	reaper;
	pthread_t	meals;

	n = i;
	if (n % 2)
		usleep(500);
	data->philos[n].last_meal = get_time();
	pthread_create(&reaper, 0, death_check, data);
	while (1)
		actions(data, n);
}

void	clean_exit(t_data *data)
{
	int	i;

	i = -1;
	sem_close(data->forks);
	sem_close(data->finish);
	//sem_close(data->reaper);
	sem_close(data->message);
	//sem_close(philos->can_die);
	sem_unlink("forks");
	sem_unlink("finish");
	//sem_unlink("reaper");
	sem_unlink("message");
	//sem_unlink("can_die");
	while (++i < data->philo_no)
		kill(data->pid[i], SIGKILL);
	free(data->philos);
	free(data->pid);
	free(data);
	exit (0);
}

/* int	death(t_data *data)
{
	unsigned int	time;
	int				i;

	i = -1;
	while (++i < data->philo_no)
	{
		time = get_time() - data->philos[i].last_meal;
		if (time > (unsigned int)data->time_to_die)
		{
			//sem_wait(philo->can_die);
			print_message(data, i, 5);
			data->dead = 1;
			return (1);
			//pthread_detach(philo->data->death);
			//pthread_detach(philo->data->done);
			//sem_post(philo->data->reaper);
			//while (++i <= philo->data->philos)
			//	sem_post(philo->data->finish);
		}
	}
	return (0);
}
 */
void	*monitoring(void *arg)
{
	t_data	*data;
	int		i;
	
	i = -1;
	data = (t_data *)arg;
	sem_wait(data->finish);
	while (++i < data->philo_no)
		kill(data->pid[i], SIGKILL);
	return (0);
}

void	*banquet_done(void *arg)
{
	t_data	*data;
	int		i;
	int		j;
	
	i = -1;
	j = 0;
	data = (t_data *)arg;
	while (1)
	{
		sem_wait(data->meals);
			j++;
		if (j == data->philo_no)
		{
			
			while (++i < data->philo_no)
				kill(data->pid[i], SIGKILL);
			return (0);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	pthread_t	monitor;
	pthread_t	banquet;
	int	i;

	i = 0;
	if (ac == 5 || ac == 6)
	{
		data = init_data(ac, av);
		data->start = get_time();
		data->index = -1;
		while (++data->index < data->philo_no)
		{
			data->pid[data->index] = fork();
			if(data->pid[data->index] == 0)
				processes(data, data->index);
		}
		pthread_create(&monitor, 0, monitoring, data);
		pthread_create(&banquet, 0, banquet_done, data);
		/* while (1)
		{
			sem_wait(data->meals);
				i++;
			if (i == data->philo_no)
				while (++i < data->philo_no)
					kill(data->pid[i], SIGKILL);
		} */
		waitpid(-1, 0, 0);
		clean_exit(data);
		return (0);
	}
	return (0);
}
