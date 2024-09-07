/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 05:38:32 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/02 09:11:38 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_parser_digit(int argc, char **argv)
{
	int	x;
	int	y;

	y = 1;
	x = 0;
	while (y < argc)
	{
		while (argv[y][x])
		{
			if ((argv[y][x] >= 48 && argv[y][x] <= 57)
				|| argv[y][x] == 43 || argv[y][x] == 45)
				x++;
			else
				return (1);
		}
		x = 0;
		y++;
	}
	return (0);
}

int	ft_parser(int argc, char **argv)
{
	long long int	nbr;

	if (ft_parser_digit(argc, argv) == 1)
		return (1);
	nbr = ft_atol(argv[1]);
	if (nbr > 300 || nbr <= 0)
		return (1);
	nbr = ft_atol(argv[2]);
	if (nbr > 2147483647 || nbr < 0)
		return (1);
	nbr = ft_atol(argv[3]);
	if (nbr > 2147483647 || nbr < 0)
		return (1);
	nbr = ft_atol(argv[4]);
	if (nbr > 2147483647 || nbr < 0)
		return (1);
	if (argc == 6)
	{
		nbr = ft_atol(argv[5]);
		if (nbr > 2147483647 || nbr < 0)
			return (1);
	}
	return (0);
}
