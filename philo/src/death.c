/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:29:46 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/02 11:02:55 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_check_death(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->m_death);
	if (philo->data->death == 1)
	{
		pthread_mutex_unlock(&philo->data->m_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_death);
	return (0);
}

void	philo_put_death(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->m_death);
	philo->data->death = 1;
	pthread_mutex_unlock(&philo->data->m_death);
}

void	main_second_death(t_data *data, int x)
{
	if (data->death == 1 || data->philos[x].meals == data->philos[x].meals_max)
	{
		pthread_mutex_unlock(data->philos[x].m_meals);
		pthread_mutex_unlock(&data->m_death);
		return ;
	}
	pthread_mutex_unlock(data->philos[x].m_meals);
	data->death = 1;
	pthread_mutex_unlock(&data->m_death);
	print_mutex("is dead", &data->philos[x], 5, data);
	return ;
}

void	main_check_death(t_data *data)
{
	int	x;

	x = 0;
	while (x <= data->nbr_philos)
	{
		if (x == data->nbr_philos)
			x = 0;
		usleep(100);
		pthread_mutex_lock(&data->m_death);
		pthread_mutex_lock(data->philos[x].m_meals);
		if (get_time() - data->philos[x].time > data->time_to_die)
		{
			main_second_death(data, x);
			return ;
		}
		pthread_mutex_unlock(data->philos[x].m_meals);
		pthread_mutex_unlock(&data->m_death);
		x++;
	}
}
