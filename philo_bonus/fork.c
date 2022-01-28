/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 02:36:32 by chasimir          #+#    #+#             */
/*   Updated: 2021/12/30 02:37:13 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_fork(t_data *param, int *pid)
{
	int	i;

	i = 0;
	while (i < param->numb_phil)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			while (i >= 0)
			{
				kill(pid[i], SIGKILL);
				i--;
			}
			exit(EXIT_FAILURE);
		}
		if (pid[i] == 0)
			fork_proc(param, i);
		i++;
	}
}

void	fork_kill_pid(t_data *param, int kill_pid, int i, int *pid)
{
	if (kill_pid == 0)
	{
		sem_wait(param->kill_proc);
		while (i < param->numb_phil)
		{
			kill(pid[i], SIGKILL);
			i++;
		}
		exit(EXIT_SUCCESS);
	}
}

void	philo_create(t_data *param)
{
	int	i;
	int	kill_pid;
	int	*pid;

	i = 0;
	pid = malloc(sizeof(int) * param->numb_phil);
	if (!pid)
		exit(EXIT_FAILURE);
	philo_fork(param, pid);
	kill_pid = fork();
	fork_kill_pid(param, kill_pid, i, pid);
	while (i < param->numb_phil)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	kill(kill_pid, SIGKILL);
	free(pid);
}
