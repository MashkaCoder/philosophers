/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 02:13:49 by chasimir          #+#    #+#             */
/*   Updated: 2021/12/30 02:15:31 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	chill_live(t_philo *philo)
{
	while (!philo->dinner->corpse
		&& philo->how_phil_eat != philo->dinner->num_times_phil_eat)
	{
		pthread_mutex_lock(&philo->dinner->fork[philo->r_fork]);
		printf("%lu %d has taken a fork\n", get_time()
			 - philo->dinner->start_time, philo->id);
		pthread_mutex_lock(&philo->dinner->fork[philo->l_fork]);
		printf("%lu %d has taken a fork\n", get_time()
			- philo->dinner->start_time, philo->id);
		printf("%lu %d is eating\n", get_time()
			- philo->dinner->start_time, philo->id);
		ft_usleep(philo->dinner->time_to_eat);
		philo->time_last_eat = get_time();
		pthread_mutex_unlock(&philo->dinner->fork[philo->r_fork]);
		pthread_mutex_unlock(&philo->dinner->fork[philo->l_fork]);
		if (philo->how_phil_eat != philo->dinner->num_times_phil_eat)
		{
			printf("%lu %d is sleeping\n", get_time()
				- philo->dinner->start_time, philo->id);
			ft_usleep(philo->dinner->time_to_sleep);
			printf("%lu %d is thinking\n", get_time()
				- philo->dinner->start_time, philo->id);
		}
		philo->how_phil_eat++;
	}
}

void	thread_create(t_data *param)
{
	int	i;

	i = 0;
	while (i < param->numb_phil)
	{
		pthread_create(&param->philo[i].thread, NULL,
			(void *)chill_live, &param->philo[i]);
		usleep(100);
		i += 2;
	}
	i = 1;
	while (i < param->numb_phil)
	{
		pthread_create(&param->philo[i].thread, NULL,
			(void *)chill_live, &param->philo[i]);
		usleep(100), i += 2;
	}
	if (chech_death(param))
		return ;
	i = 0;
	while (i < param->numb_phil)
	{
		pthread_join(param->philo[i].thread, NULL);
		i++;
	}
}

int	chech_death(t_data *param)
{
	int				i;
	unsigned long	now_t;

	i = 0;
	while (1)
	{
		while (i < param->numb_phil)
		{
			now_t = get_time();
			if (param->philo[i].how_phil_eat == param->num_times_phil_eat)
				return (1);
			if (now_t - param->philo[i].time_last_eat
				 > (unsigned long)param->time_to_die)
			{
				param->corpse = 1;
				printf(RED "%lu %d died\n", now_t - param->start_time, i + 1);
				return (1);
			}
			i++;
		}
		i = 0;
		usleep(1000);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	param;
	int		i;

	if (read_argv(argv, &param, argc))
	{
		printf("Wrong argument\n");
		return (1);
	}
	if (init_phil_fork(&param))
		return (1);
	param.start_time = get_time();
	thread_create(&param);
	free(param.fork);
	free(param.philo);
	i = 0;
	while (i < param.numb_phil)
	{
		pthread_mutex_destroy(&param.fork[i]);
		i++;
	}
	return (0);
}
