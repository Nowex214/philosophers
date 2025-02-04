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

static void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("Philosopher %d take left fork🍴\n", philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("Philosopher %d take right fork🍴\n", philo->id);
}

static void	eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->write_m);
	printf("Philosopher %d eat🍝\n", philo->id);
	pthread_mutex_unlock(data->write_m);
	philo->time_die = get_time_in_ms() + data->death_time;
	usleep(data->eat_time * 1000);
	philo->count_eat++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	printf("Philosopher %d drop his forks ⬇️🍴\n", philo->id);
}

static void	sleep_philo(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->write_m);
	printf("Philosopher %d sleep 😴\n", philo->id);
	pthread_mutex_unlock(data->write_m);
	usleep(data->sleep_time * 1000);
}

static void	think(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->write_m);
	printf("Philosopher %d think 💭\n", philo->id);
	pthread_mutex_unlock(data->write_m);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	pthread_mutex_lock(data->write_m);
	printf("🟢 Philosopher %d start\n", philo->id);
	pthread_mutex_unlock(data->write_m);
	while (!data->end)
	{
		take_fork(philo);
		eat(philo, data);
		sleep_philo(philo, data);
		think(philo, data);
	}
	return (NULL);
}