/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehenry <ehenry@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 22:50:11 by ehenry            #+#    #+#             */
/*   Updated: 2025/01/31 22:50:11 by ehenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

double	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec * 1000.0 + (double)tv.tv_usec / 1000.0);
}

int	wait_thread(t_data *data)
{
	int	i;

	i = 0;
	if (data->nb_philo == 1)
		return (0);
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			printf("❌ Error: pthread_join failed for %d\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	pthread_mutex_destroy(data->end_m);
	pthread_mutex_destroy(data->write_m);
	free(data->end_m);
	free(data->write_m);
	free(data->philos);
}
