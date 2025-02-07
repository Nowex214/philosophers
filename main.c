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
	cleanup(&data);
	return (0);
}
