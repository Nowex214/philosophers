/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehenry <ehenry@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:22:52 by ehenry            #+#    #+#             */
/*   Updated: 2025/02/09 21:07:01 by ehenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_one(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(data->write_m);
	printf("Philosopher %d has taken left fork 🍴\n", philo->id);
	pthread_mutex_unlock(data->write_m);
	usleep(data->death_time * 1000);
	pthread_mutex_lock(data->write_m);
	printf("🪦 Philosopher %d is dead (alone) !\n", philo->id);
	pthread_mutex_unlock(data->write_m);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

static void	cycle(t_philo *philo, t_data *data)
{
	data->finish_eating = 0;
	while (1)
	{
		pthread_mutex_lock(data->end_m);
		if (data->end)
		{
			pthread_mutex_unlock(data->end_m);
			break ;
		}
		pthread_mutex_unlock(data->end_m);
		take_forks(philo);
		eat(philo, data);
		if (data->nb_eat >= 0 && philo->count_eat == data->nb_eat)
		{
			pthread_mutex_lock(data->end_m);
			data->finish_eating++;
			if (data->finish_eating == data->nb_philo)
				data->end = 1;
			pthread_mutex_unlock(data->end_m);
			break ;
		}
		sleep_philo(philo, data);
		think(philo, data);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 != 0)
		usleep(1000);
	cycle(philo, data);
	return (NULL);
}
