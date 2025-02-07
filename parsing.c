/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehenry <ehenry@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:51:18 by ehenry            #+#    #+#             */
/*   Updated: 2025/02/07 09:51:18 by ehenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_arg(int ac, char **av, t_data *data)
{
	if (ac < 5)
	{
		printf("🤓☝️ Maybe try: ./philo <nb_philo> <time_to_die> <time_to_eat>"
			"<time_to_sleep> [nb_eat]\n");
		return (1);
	}
	data->nb_philo = ft_atoi(av[1]);
	data->death_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5]);
	else
		data->nb_eat = -1;
	if (data->nb_philo < 1 || data->death_time < 0 || data->eat_time < 0
		|| data->sleep_time < 0 || (ac == 6 && data->nb_eat < 0))
	{
		printf("❌ Error: All arguments must be positive integers.\n");
		return (1);
	}
	data->end = 0;
	data->dead = 0;
	return (0);
}

static int	check_philo(t_data *data)
{
	int		i;
	double	now;

	i = 0;
	while (i < data->nb_philo)
	{
		now = get_time_in_ms();
		pthread_mutex_lock(data->end_m);
		if ((unsigned int)now > data->philos[i].time_die && data->end == 0)
		{
			printf("🪦 Philosopher %d is dead !\n", data->philos[i].id);
			data->end = 1;
			pthread_mutex_unlock(data->end_m);
			return (1);
		}
		pthread_mutex_unlock(data->end_m);
		i++;
	}
	return (0);
}

void	*monitor_thread(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (!data->philos)
		return (NULL);
	while (1)
	{
		if (check_philo(data))
			return (NULL);
		usleep(1000);
		pthread_mutex_lock(data->end_m);
		if (data->end == 1)
		{
			pthread_mutex_unlock(data->end_m);
			break ;
		}
		pthread_mutex_unlock(data->end_m);
	}
	return (NULL);
}
