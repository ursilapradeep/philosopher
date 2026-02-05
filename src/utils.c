/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:54:46 by uvadakku          #+#    #+#             */
/*   Updated: 2026/02/03 15:59:36 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_dead(t_philosophers *philo, size_t time_to_die)
{
	long	current_time;

	current_time = get_current_time();
	if ((size_t)(current_time - philo->last_meal_time) >= time_to_die)
		return (1);
	return (0);
}

int	check_if_dead(t_philosophers *philo)
{
	t_monitor	*monitor;
	int			dead;

	monitor = philo->monitor;
	pthread_mutex_lock(&monitor->dead_lock);
	dead = monitor->dead_flag;
	pthread_mutex_unlock(&monitor->dead_lock);
	return (dead);
}

void	print_routine(t_philosophers *philo, const char *action)
{
	long		current_timestamp;
	t_monitor	*monitor;

	monitor = philo->monitor;
	current_timestamp = get_current_time() - monitor->start_time;
	pthread_mutex_lock(&monitor->w_lock);
	if (!monitor->end_status)
		printf("%ld %d %s\n", current_timestamp,
			philo->id, action);
	pthread_mutex_unlock(&monitor->w_lock);
}
