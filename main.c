/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehenry <ehenry@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:22:40 by ehenry            #+#    #+#             */
/*   Updated: 2025/02/01 15:22:40 by ehenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (parse_arg(ac, av, &data) != 0)
		return (1);
	if (init_mutex(&data) != 0)
	{
		printf("❌ Error: init_mutex failed\n");
		return (1);
	}
	if (init_forks(&data) != 0)
	{
		printf("❌ Error: init_forks failed\n");
		return (1);
	}
	if (init_philo(&data) != 0)
	{
		printf("❌ Error: init_philo failed\n");
		return (1);
	}
	if (init_thread(&data) != 0)
	{
		printf("❌ Error: init_thread failed\n");
		return (1);
	}
	if (wait_thread(&data) != 0)
	{
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}
