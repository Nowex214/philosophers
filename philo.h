/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehenry <ehenry@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 22:27:34 by ehenry            #+#    #+#             */
/*   Updated: 2025/01/31 22:27:34 by ehenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				count_eat;
	int				eating;
	int				status;
	unsigned int	time_die;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	lock;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				nb_eat;
	int				end;
	int				dead;
	unsigned int	start_time;
	int				sleep_time;
	int				eat_time;
	int				death_time;
	pthread_t		*threads;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*write_m;
	pthread_mutex_t	*end_m;
}	t_data;

// Parsing / Init
int		parse_arg(int ac, char **av, t_data *data);
int		init_mutex(t_data *data);
int		init_forks(t_data *data);
int		init_philo(t_data *data);
int		init_thread(t_data *data);

// Routine / Monitor
void	*routine(void *arg);
void	*monitor_thread(void *arg);
void	*routine_one(void *arg);

// Utils
int		ft_atoi(const char *str);
int		wait_thread(t_data *data);
void	cleanup(t_data *data);
double	get_time_in_ms(void);

#endif
