/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_init_param.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 02:44:17 by chasimir          #+#    #+#             */
/*   Updated: 2021/12/30 02:44:24 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (argc == 6)
		param->num_times_phil_eat = ft_atoi(argv[5]);
	else
		param->num_times_phil_eat = -1;
	if (check_param(param))
		return (1);
	return (0);
}

void	sem_init_m(t_data *param)
{
	sem_unlink("p_fork");
	param->fork = sem_open("p_fork", O_CREAT | O_EXCL, 0664, param->numb_phil);
	if (param->fork == SEM_FAILED)
	{
		sem_close(param->fork);
		exit(EXIT_FAILURE);
	}
	sem_unlink("p_kill");
	param->kill_proc = sem_open("p_kill", O_CREAT | O_EXCL, 0664, 0);
	if (param->kill_proc == SEM_FAILED)
	{
		sem_close(param->kill_proc);
		exit(EXIT_FAILURE);
	}
}

void	close_sem(t_data *param)
{
	if (param->fork)
	{
		sem_close(param->fork);
		sem_unlink("p_fork");
	}
	if (param->kill_proc)
	{
		sem_close(param->kill_proc);
		sem_unlink("p_kill");
	}
}
