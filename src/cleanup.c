/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:15:49 by uvadakku          #+#    #+#             */
/*   Updated: 2026/01/28 12:20:32 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	join_threads(t_monitor *monitor, pthread_t monitor_thread)
{
	int	i;

	if (!monitor || !monitor->philosophers)
		return (1);
	i = 0;
	while (i < monitor->philosopher_count)
	{
		if (pthread_join(monitor->philosophers[i].thread, NULL) != 0)
		{
			printf("Failed to join philosopher thread\n");
			return (1);
		}
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		printf("Failed to join monitor thread\n");
		return (1);
	}
	return (0);
}

static void	destroy_philosopher_mutexes(t_monitor *monitor)
{
	int	i;

	if (!monitor)
		return ;
	i = 0;
	while (i < monitor->philosopher_count)
	{
		pthread_mutex_destroy(&monitor->philosophers[i].dead_lock);
		pthread_mutex_destroy(&monitor->philosophers[i].meal_lock);
		i++;
	}
}

static void	destroy_forks(t_monitor *monitor)
{
	int	i;

	if (!monitor || !monitor->forks)
		return ;
	i = 0;
	while (i < monitor->philosopher_count)
	{
		pthread_mutex_destroy(&monitor->forks[i]);
		i++;
	}
}

static void	destroy_shared_mutexes(t_monitor *monitor)
{
	if (!monitor)
		return ;
	pthread_mutex_destroy(&monitor->w_lock);
	pthread_mutex_destroy(&monitor->dead_lock);
	pthread_mutex_destroy(&monitor->meal_lock);
}

void	cleanup_simulation(t_monitor *monitor)
{
	if (!monitor)
		return ;
	destroy_philosopher_mutexes(monitor);
	destroy_forks(monitor);
	destroy_shared_mutexes(monitor);
	if (monitor->philosophers)
		free(monitor->philosophers);
	if (monitor->forks)
		free(monitor->forks);
	free(monitor);
}
