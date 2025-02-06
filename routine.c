/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehenry <ehenry@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:59:30 by ehenry            #+#    #+#             */
/*   Updated: 2025/02/01 12:59:30 by ehenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->data->write_m);
	printf("Philosopher %d has taken left fork 🍴\n", philo->id);
	pthread_mutex_unlock(philo->data->write_m);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->data->write_m);
	printf("Philosopher %d has taken right fork 🍴\n", philo->id);
	pthread_mutex_unlock(philo->data->write_m);
}

static void	eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->write_m);
	printf("Philosopher %d is eating 🍝\n", philo->id);
	pthread_mutex_unlock(data->write_m);
	philo->time_die = (unsigned int)get_time_in_ms() + data->death_time;
	usleep(data->eat_time * 1000);
	philo->count_eat++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(data->write_m);
	printf("Philosopher %d drops forks ⬇️🍴\n", philo->id);
	pthread_mutex_unlock(data->write_m);
}

static void	sleep_philo(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->write_m);
	printf("Philosopher %d is sleeping 😴\n", philo->id);
	pthread_mutex_unlock(data->write_m);
	usleep(data->sleep_time * 1000);
}

static void	think(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->write_m);
	printf("Philosopher %d is thinking 💭\n", philo->id);
	pthread_mutex_unlock(data->write_m);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 != 0)
		usleep(1000);
	pthread_mutex_lock(data->write_m);
	printf("🟢 Philosopher %d starts\n", philo->id);
	pthread_mutex_unlock(data->write_m);
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
		if (data->nb_eat > 0 && philo->count_eat >= data->nb_eat)
		{
			pthread_mutex_lock(data->end_m);
			printf("🎉 Philosophers %d have finished eating %d times\n", philo->id, data->nb_eat);
			data->end = 1;
			pthread_mutex_unlock(data->end_m);
			break ;
		}
		sleep_philo(philo, data);
		think(philo, data);
	}
	return (NULL);
}
