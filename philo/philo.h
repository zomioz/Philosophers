/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:15:28 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/06 14:15:29 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philos
{
	pthread_t		philo;
	pthread_mutex_t	*f_left;
	pthread_mutex_t	*f_right;
	int				place;
	int				max;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time;
	pthread_mutex_t	*m_meals;
	int				meals_max;
	int				meals;
	struct s_data	*data;
}	t_philos;

typedef struct s_data
{
	int				nbr_philos;
	int				death;
	size_t			time_ref;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_mutex_t	write;
	pthread_mutex_t	m_death;
	struct s_philos	*philos;
}	t_data;

//PARSER
int				ft_parser_digit(int argc, char **argv);
int				ft_parser(int argc, char **argv);

//UTILS
size_t			ft_atoi(const char *nptr);
long long int	ft_atol(const char *nptr);
size_t			get_time(void);
void			print_mutex(char *cont, t_philos *philo, int col, t_data *data);
int				ft_usleep(size_t milliseconds);

//TABLE
int				file_philo(t_philos *ph, int ac, char **av, t_data *data);
int				create_philos(t_data *data, char **argv, int argc);
int				file_data(t_data *data, char **argv, int argc);
void			free_data(t_data *data);

//EATING
void			death_while_eating(t_philos *philo);
void			eating(t_philos *philo);
int				fork_last_philo(t_philos *philo);
int				fork_all_philo(t_philos *philos);
int				philo_meal(t_philos *philo);

//ROUTINE
void			*rout(void *content);

//DEATH
int				philo_check_death(t_philos *philo);
void			philo_put_death(t_philos *philo);
void			main_second_death(t_data *data, int x);
void			main_check_death(t_data *data);

int				philo_check_death(t_philos *philo);
void			philo_put_death(t_philos *philo);

#endif
