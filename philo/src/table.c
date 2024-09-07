/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 06:18:31 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/02 11:00:55 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_error(t_data *data, int x)
{
	while (x >= 0)
	{
		pthread_mutex_destroy(data->philos[x].m_meals);
		pthread_mutex_destroy(data->philos[x].f_right);
		free(data->philos[x].m_meals);
		free(data->philos[x].f_right);
		x--;
	}
}

int	file_philo(t_philos *ph, int ac, char **av, t_data *data)
{
	ph->m_meals = malloc(sizeof(pthread_mutex_t));
	if (!ph->m_meals)
		return (1);
	ph->time_to_die = ft_atoi(av[2]);
	ph->time_to_eat = ft_atoi(av[3]);
	ph->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		ph->meals_max = ft_atoi(av[5]);
	else
		ph->meals_max = -1;
	ph->meals = 0;
	ph->data = data;
	ph->max = data->nbr_philos;
	ph->f_left = 0;
	ph->f_right = malloc(sizeof(pthread_mutex_t));
	if (!ph->f_right)
	{
		free(ph->m_meals);
		return (1);
	}
	return (0);
}

int	create_philos(t_data *data, char **argv, int argc)
{
	int	x;

	x = 0;
	while (x < data->nbr_philos)
	{
		data->philos[x].place = x + 1;
		if (file_philo(&data->philos[x], argc, argv, data) == 1)
		{
			if (x > 0)
				free_error(data, x - 1);
			return (1);
		}
		pthread_mutex_init(data->philos[x].m_meals, NULL);
		pthread_mutex_init(data->philos[x].f_right, NULL);
		if (x > 0)
			data->philos[x].f_left = data->philos[x - 1].f_right;
		if (x == data->nbr_philos - 1 && data->nbr_philos > 1)
			data->philos[0].f_left = data->philos[x].f_right;
		x++;
	}
	return (0);
}

int	file_data(t_data *data, char **argv, int argc)
{
	data->nbr_philos = ft_atoi(argv[1]);
	data->philos = malloc(sizeof(t_philos) * data->nbr_philos);
	if (!data->philos)
		return (1);
	data->death = 0;
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->time_to_die = ft_atoi(argv[2]);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->m_death, NULL);
	if (create_philos(data, argv, argc) == 1)
	{
		pthread_mutex_destroy(&data->write);
		pthread_mutex_destroy(&data->m_death);
		free(data->philos);
		return (1);
	}
	return (0);
}

void	free_data(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->nbr_philos)
	{
		pthread_mutex_destroy(data->philos[x].f_right);
		pthread_mutex_destroy(data->philos[x].m_meals);
		x++;
	}
	x = 0;
	while (x < data->nbr_philos)
	{
		free(data->philos[x].m_meals);
		free(data->philos[x].f_right);
		x++;
	}
	free(data->philos);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->m_death);
	free(data);
}
