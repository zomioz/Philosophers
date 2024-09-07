/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:21:00 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/02 10:47:13 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*rout(void *content)
{
	t_philos	*philo;

	philo = (t_philos *)content;
	if ((philo->place - 1) % 2 == 1)
		usleep(1000);
	if (philo_check_death(philo) == 1)
		return (0);
	print_mutex("is thinking", philo, 1, philo->data);
	if (philo_check_death(philo) == 1)
		return (0);
	if (philo_meal(philo) == 1)
		return (0);
	if (philo->meals_max != -1 && philo->meals == philo->meals_max)
	{
		print_mutex("Philo finished all his meals", philo, 5, philo->data);
		return (0);
	}
	if (philo_check_death(philo) == 1)
		return (0);
	print_mutex("is sleeping", philo, 4, philo->data);
	ft_usleep(philo->time_to_sleep);
	rout(philo);
	return (0);
}
