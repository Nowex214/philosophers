/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehenry <ehenry@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:19:08 by ehenry            #+#    #+#             */
/*   Updated: 2025/02/01 12:19:08 by ehenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_arg(int ac, char **av, t_data *data)
{
	if (ac < 5)
	{
		printf ("🤓☝️Try: ./philo <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> [nb_eat]\n");
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
	if (data->nb_philo < 0 || data->death_time < 0 || data->eat_time < 0 ||
		data->sleep_time < 0 ||(ac == 6 && data->nb_eat < 0))
	{
		printf ("❌ Error: All arg need to be positif number.\n");
		return(1);
	}
	return (0);
}

void	*monitor_thread(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;

	if (!data->philos)
		return (NULL);
	while (!data->end)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (get_time_in_ms() > data->philos[i].time_die)
			{
				printf("🪦 Philosophers %d is dead !\n", data->philos[i].id);
				pthread_mutex_lock(data->end_m);
				data->end = 1;
				pthread_mutex_unlock(data->end_m);
				break;
			}
			i++;
		}
		usleep(data->philos->time_die * 1000);
	}
	return (NULL);
}
