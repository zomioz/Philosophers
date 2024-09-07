/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 02:40:06 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/02 09:11:32 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	ft_atoi(const char *nptr)
{
	int	sign;
	int	stock;
	int	x;

	x = 0;
	stock = 0;
	sign = 1;
	while ((nptr[x] >= 9 && nptr[x] <= 13) || nptr[x] == 32)
		x++;
	if (nptr[x] == '-' || nptr[x] == '+')
	{
		if (nptr[x + 1] == '-' || nptr[x + 1] == '+')
			return (0);
		if (nptr[x] == '-')
			sign *= -1;
		x++;
	}
	while (nptr[x] >= '0' && nptr[x] <= '9')
	{
		stock = (stock * 10) + (nptr[x] - 48);
		x++;
	}
	return (stock * sign);
}

long long int	ft_atol(const char *nptr)
{
	int	sign;
	int	stock;
	int	x;

	x = 0;
	stock = 0;
	sign = 1;
	while ((nptr[x] >= 9 && nptr[x] <= 13) || nptr[x] == 32)
		x++;
	if (nptr[x] == '-' || nptr[x] == '+')
	{
		if (nptr[x + 1] == '-' || nptr[x + 1] == '+')
			return (0);
		if (nptr[x] == '-')
			sign *= -1;
		x++;
	}
	while (nptr[x] >= '0' && nptr[x] <= '9')
	{
		stock = (stock * 10) + (nptr[x] - 48);
		x++;
	}
	return (stock * sign);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_mutex(char *cont, t_philos *philo, int col, t_data *data)
{
	size_t	time;

	pthread_mutex_lock(&data->write);
	time = get_time() - data->time_ref;
	if (col == 1)
		printf("\033[0;32m");
	else if (col == 1)
		printf("\033[0;33m");
	else if (col == 2)
		printf("\033[0;34m");
	else if (col == 3)
		printf("\033[0;35m");
	else if (col == 4)
		printf("\033[0;36m");
	else
		printf("\033[0;31m");
	printf("%zu %d %s\n", time, philo->place, cont);
	printf("\033[0;37m");
	pthread_mutex_unlock(&data->write);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
