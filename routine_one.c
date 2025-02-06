/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehenry <ehenry@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:22:52 by ehenry            #+#    #+#             */
/*   Updated: 2025/02/06 12:23:44 by ehenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_one(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;

	pthread_mutex_lock(data->write_m);
	printf("🟢 Philosopher %d starts\n", philo->id);
	pthread_mutex_unlock(data->write_m);

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
