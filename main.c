/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehenry <ehenry@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:51:06 by ehenry            #+#    #+#             */
/*   Updated: 2025/02/07 09:51:06 by ehenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_error(const char *msg, t_data *data)
{
	printf("❌ Error: %s\n", msg);
	if (data)
		cleanup(data);
	return (1);
}

static void	print_final(t_data *data)
{
	int	i;

	pthread_mutex_lock(data->write_m);
	printf("\n=====🎀=====✨𝒩𝓊𝓂𝒷𝑒𝓇 𝑒𝒶𝓉 𝒻𝒾𝓃𝒶𝓁✨=====🎀=====\n");
	i = 0;
	while (i < data->nb_philo)
	{
		printf("🔎👀 Philosopher %d ate %d times\n",
			data->philos[i].id, data->philos[i].count_eat);
		i++;
	}
	pthread_mutex_unlock(data->write_m);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (parse_arg(ac, av, &data) != 0)
		return (handle_error("Invalid arguments", NULL));
	if (init_mutex(&data) != 0)
		return (handle_error("init_mutex failed", NULL));
	if (init_forks(&data) != 0)
		return (handle_error("init_forks failed", &data));
	if (init_philo(&data) != 0)
		return (handle_error("init_philo failed", &data));
	if (init_thread(&data) != 0)
		return (handle_error("init_thread failed", &data));
	if (wait_thread(&data) != 0)
		return (handle_error("wait_thread failed", &data));
	print_final(&data);
	cleanup(&data);
	return (0);
}
