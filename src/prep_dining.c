/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_dining.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:59:31 by uvadakku          #+#    #+#             */
/*   Updated: 2026/01/27 12:25:07 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	initialize_forks(t_monitor *monitor)
{
	pthread_mutex_t	*forks;
	int				num_forks;

	num_forks = 0;
	forks = malloc (sizeof(pthread_mutex_t) * monitor->philosopher_count);
	if (!forks)
	{
		printf("Memory allocation for forks failed\n");
		return ;
	}
	while (num_forks < monitor -> philosopher_count)
	{
		pthread_mutex_init(&forks[num_forks], NULL);
		num_forks++;
	}
	monitor->forks = forks;
}

void	initialize_philosophers(t_monitor *monitor)
{
	int	i;

	i = 0;
	monitor->philosophers = malloc(sizeof(t_philosophers)
			* monitor->philosopher_count);
	if (!monitor->philosophers)
	{
		printf(" Memory allocation for philosophers failed\n ");
		return ;
	}
	while (i < monitor->philosopher_count)
	{
		monitor->philosophers[i].id = i + 1;
		monitor->philosophers[i].meals_eaten = 0;
		monitor->philosophers[i].meals_required = monitor->required_meals;
		monitor->philosophers[i].monitor = monitor;
		pthread_mutex_init(&monitor->philosophers[i].dead_lock, NULL);
		pthread_mutex_init(&monitor->philosophers[i].meal_lock, NULL);
		i++;
	}
}

void	assign_forks_to_philosophers(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->philosopher_count)
	{
		monitor->philosophers[i].left_fork = &monitor->forks[i];
		monitor->philosophers[i].right_fork = &monitor->forks[(i + 1)
			% monitor->philosopher_count];
		i++;
	}
}
