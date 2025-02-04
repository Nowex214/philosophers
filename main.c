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

	data.end = 0;
	if (parse_arg(ac, av, &data) != 0)
		return (1);
	if (init_mutex(&data) != 0)
	{
		printf("❌ Error: init mutex failed\n");
		return (1);
	}
	if (init_forks(&data) != 0)
	{
		printf("❌ Error: init forks failed\n");
		return (1);
	}
	if (init_philo(&data) != 0)
	{
		printf("❌ Error: init philos failed\n");
		return (1);
	}
	if (init_thread(&data) != 0)
	{
		printf("❌ Error: init thread failed\n");
		return (1);
	}
	wait_thread(&data);
	cleanup(&data);
	return (0);
}
