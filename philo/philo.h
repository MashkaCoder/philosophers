/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 02:14:25 by chasimir          #+#    #+#             */
/*   Updated: 2021/12/30 02:18:00 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED	"\x1b[31m"

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_philo
{
	int				id;
	int				how_phil_eat;
	int				r_fork;
	int				l_fork;
	pthread_t		thread;
	unsigned long	time_last_eat;
	struct s_data	*dinner;
}				t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	unsigned long	start_time;
	int				numb_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_phil_eat;
	int				corpse;
}				t_data;

// check_and_init_param.c
int				check_param(t_data *param);
int				read_argv(char **argv, t_data *param, int argc);
void			init_phil(t_data *param, int i);
int				init_phil_fork(t_data *param);

// time.c
unsigned long	get_time(void);
void			ft_usleep(int time_to_wait);

//ft_atoi.c
int				ft_atoi(const char *str);

// philo.c
int				chech_death(t_data *param);
void			thread_create(t_data *param);
void			chill_live(t_philo *philo);

#endif
