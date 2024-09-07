/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:16:26 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/02 10:22:00 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	death_while_eating(t_philos *philo)
{
	print_mutex("is eating", philo, 3, philo->data);
	ft_usleep(philo->time_to_die);
	pthread_mutex_unlock(philo->f_left);
	pthread_mutex_unlock(philo->f_right);
	if (philo_check_death(philo) == 1)
		return ;
	print_mutex("is dead", philo, 5, philo->data);
	philo_put_death(philo);
	return ;
}

void	eating(t_philos *philo)
{
	print_mutex("is eating", philo, 3, philo->data);
	pthread_mutex_lock(philo->m_meals);
	philo->meals++;
	philo->time = get_time();
	pthread_mutex_unlock(philo->m_meals);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->f_left);
	pthread_mutex_unlock(philo->f_right);
	return ;
}

int	fork_last_philo(t_philos *philo)
{
	pthread_mutex_lock(philo->f_right);
	if (philo_check_death(philo) == 1)
	{
		pthread_mutex_unlock(philo->f_right);
		return (1);
	}
	print_mutex("has taken a fork", philo, 2, philo->data);
	pthread_mutex_lock(philo->f_left);
	if (philo_check_death(philo) == 1)
	{
		pthread_mutex_unlock(philo->f_right);
		pthread_mutex_unlock(philo->f_left);
		return (1);
	}
	print_mutex("has taken a fork", philo, 2, philo->data);
	return (0);
}

int	fork_all_philo(t_philos *philo)
{
	pthread_mutex_lock(philo->f_left);
	if (philo_check_death(philo) == 1)
	{
		pthread_mutex_unlock(philo->f_left);
		return (1);
	}
	print_mutex("has taken a fork", philo, 2, philo->data);
	pthread_mutex_lock(philo->f_right);
	if (philo_check_death(philo) == 1)
	{
		pthread_mutex_unlock(philo->f_left);
		pthread_mutex_unlock(philo->f_right);
		return (1);
	}
	print_mutex("has taken a fork", philo, 2, philo->data);
	return (0);
}

int	philo_meal(t_philos *philo)
{
	if (philo->place == philo->max)
	{
		if (fork_last_philo(philo) == 1)
			return (1);
	}
	else
	{
		if (fork_all_philo(philo) == 1)
			return (1);
	}
	if (philo_check_death(philo) == 1)
	{
		pthread_mutex_unlock(philo->f_left);
		pthread_mutex_unlock(philo->f_right);
		return (1);
	}
	if (philo->time_to_die <= philo->time_to_eat)
	{
		death_while_eating(philo);
		return (1);
	}
	eating(philo);
	return (0);
}
