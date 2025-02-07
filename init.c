/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehenry <ehenry@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:50:56 by ehenry            #+#    #+#             */
/*   Updated: 2025/02/07 09:50:56 by ehenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("❌ Error: mutex init fork %d failed\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (1);
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].count_eat = 0;
		data->philos[i].eating = 0;
		data->philos[i].status = 0;
		data->philos[i].time_die = get_time_in_ms() + data->death_time;
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	data->end_m = malloc(sizeof(pthread_mutex_t));
	data->write_m = malloc(sizeof(pthread_mutex_t));
	if (!data->end_m || !data->write_m)
		return (1);
	if (pthread_mutex_init(data->end_m, NULL) != 0
		|| pthread_mutex_init(data->write_m, NULL) != 0)
	{
		free(data->write_m);
		free(data->end_m);
		return (1);
	}
	return (0);
}

static int	create_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]) != 0)
		{
			printf("❌ Error: Impossible to create thread of "
				"Philosopher %d ☠️\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_thread(t_data *data)
{
	pthread_t	monitor;

	if (data->nb_philo == 1)
	{
		routine_one(&data->philos[0]);
		return (0);
	}
	if (create_philo(data) != 0)
		return (1);
	if (pthread_create(&monitor, NULL, &monitor_thread, data) != 0)
	{
		printf("❌ Error: Impossible to create monitor thread..\n");
		return (1);
	}
	pthread_join(monitor, NULL);
	return (0);
}
