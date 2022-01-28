/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 02:38:35 by chasimir          #+#    #+#             */
/*   Updated: 2021/12/30 02:38:36 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(t_philo *philo)
{
	unsigned long	now_time;

	while (1)
	{
		now_time = get_time();
		if (philo->how_phil_eat == philo->dinner->num_times_phil_eat)
			return (NULL);
		if (now_time - philo->time_last_eat
			 >= (unsigned long)philo->dinner->time_to_die)
		{
			sem_post(philo->dinner->kill_proc);
			philo->corpse = 1;
			printf(RED "%lu %d died\n",
				 now_time - philo->dinner->start_time, philo->id);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	print_xiy(t_philo *philo)
{
	while (!philo->corpse
		&& philo->how_phil_eat != philo->dinner->num_times_phil_eat)
	{
		sem_wait(philo->dinner->fork);
		printf("%lu %d has taken a fork\n",
			get_time() - philo->dinner->start_time, philo->id);
		sem_wait(philo->dinner->fork);
		printf("%lu %d has taken a fork\n",
			get_time() - philo->dinner->start_time, philo->id);
		printf("%lu %d is eating\n", get_time()
			 - philo->dinner->start_time, philo->id);
		ft_usleep(philo->dinner->time_to_eat);
		philo->time_last_eat = get_time();
		philo->how_phil_eat++;
		sem_post(philo->dinner->fork);
		sem_post(philo->dinner->fork);
		if (philo->how_phil_eat != philo->dinner->num_times_phil_eat)
		{
			printf("%lu %d is sleeping\n",
				 get_time() - philo->dinner->start_time, philo->id);
			ft_usleep(philo->dinner->time_to_sleep);
			printf("%lu %d is thinking\n",
				 get_time() - philo->dinner->start_time, philo->id);
		}
	}
}

void	fork_proc(t_data *param, int i)
{
	t_philo	philo;

	philo.corpse = 0;
	philo.dinner = param;
	philo.how_phil_eat = 0;
	philo.id = i + 1;
	philo.time_last_eat = get_time();
	pthread_create(&philo.thread, NULL, (void *)check_death, &philo);
	print_xiy(&philo);
	pthread_detach(philo.thread);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	param;
	int		i;

	if (read_argv(argv, &param, argc))
	{
		printf("Wrong argument\n");
		exit(EXIT_FAILURE);
	}
	sem_init_m(&param);
	param.start_time = get_time();
	philo_create(&param);
	close_sem(&param);
	exit(EXIT_SUCCESS);
}
