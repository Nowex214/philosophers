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

void	take_forks(t_philo *philo)
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

void	eat(t_philo *philo, t_data *data)
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

void	sleep_philo(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->write_m);
	printf("Philosopher %d is sleeping 😴\n", philo->id);
	pthread_mutex_unlock(data->write_m);
	usleep(data->sleep_time * 1000);
}

void	think(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->write_m);
	printf("Philosopher %d is thinking 💭\n", philo->id);
	pthread_mutex_unlock(data->write_m);
}
