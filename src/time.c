/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:07:54 by uvadakku          #+#    #+#             */
/*   Updated: 2026/01/19 10:53:55 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_current_time(void)
{
	struct timeval	tv;
	long long		time_in_millisec;

	if (gettimeofday(&tv, NULL) != 0)
	{
		perror("gettimeofday");
		return (-1);
	}
	time_in_millisec = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_millisec);
}

void	sleep_ms(unsigned int ms)
{
	long	start_time;
	long	current_time;

	start_time = get_current_time() * 1000;
	current_time = start_time;
	while ((current_time - start_time) < (long)(ms * 1000))
	{
		usleep(100);
		current_time = get_current_time() * 1000;
	}
}
