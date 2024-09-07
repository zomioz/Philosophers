/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 04:27:21 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/02 11:03:32 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*one(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	print_mutex("is thinking", philo, 1, philo->data);
	pthread_mutex_lock(philo->f_right);
	print_mutex("has taken a fork", philo, 2, philo->data);
	ft_usleep(philo->time_to_die);
	print_mutex("is dead", philo, 5, philo->data);
	pthread_mutex_unlock(philo->f_right);
	return (0);
}

int	launch_thread(t_data *da)
{
	int	x;

	x = 0;
	da->time_ref = get_time();
	if (da->nbr_philos == 1)
	{
		pthread_create(&da->philos[x].philo, NULL, &one, &da->philos[x]);
		return (1);
	}
	while (x < da->nbr_philos)
	{
		da->philos[x].time = get_time();
		if (pthread_create(&da->philos[x].philo, NULL, &rout, &da->philos[x]))
		{
			printf("Error when creating a thread !\n");
			return (1);
		}
		x++;
	}
	return (0);
}

void	join_thread(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->nbr_philos)
	{
		pthread_join(data->philos[x].philo, NULL);
		x++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (printf("Please enter valid arguments !\n"));
	if (ft_parser(argc, argv) == 1)
	{
		printf("Please enter valid arguments !\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("Error malloc, end of program\n"));
	if (file_data(data, argv, argc) == 1)
	{
		free(data);
		return (printf("Error malloc, end of program\n"));
	}
	if (launch_thread(data) == 0)
		main_check_death(data);
	join_thread(data);
	free_data(data);
	return (0);
}
