/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_init_param.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 02:02:56 by chasimir          #+#    #+#             */
/*   Updated: 2021/12/30 02:02:57 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_param(t_data *param)
{
	if (param->numb_phil <= 0 || param->time_to_die <= 0
		|| param->time_to_sleep <= 0 || param->time_to_eat <= 0)
		return (1);
	return (0);
}

int	read_argv(char **argv, t_data *param, int argc)
{
	if (argc != 5 && argc != 6)
		return (1);
	param->numb_phil = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	param->corpse = 0;
	if (argc == 6)
		param->num_times_phil_eat = ft_atoi(argv[5]);
	else
		param->num_times_phil_eat = -1;
	if (check_param(param))
		return (1);
	return (0);
}

void	init_phil(t_data *param, int i)
{
	param->philo[i].id = i + 1;
	param->philo[i].r_fork = i;
	param->philo[i].dinner = param;
	param->philo[i].how_phil_eat = 0;
	if (i == 0)
		param->philo[i].l_fork = param->numb_phil - 1;
	else
		param->philo[i].l_fork = i - 1;
	param->philo[i].time_last_eat = get_time();
}

int	init_phil_fork(t_data *param)
{
	int	i;

	i = 0;
	param->philo = malloc(sizeof(t_philo) * param->numb_phil);
	if (!param->philo)
		return (1);
	param->fork = malloc(sizeof(pthread_mutex_t) * param->numb_phil);
	if (!param->fork)
	{
		free(param->philo);
		return (1);
	}
	while (i < param->numb_phil)
	{
		pthread_mutex_init(&param->fork[i], NULL);
		init_phil(param, i);
		i++;
	}
	return (0);
}
