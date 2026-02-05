/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:19:19 by uvadakku          #+#    #+#             */
/*   Updated: 2026/02/04 11:52:28 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_phil_threads(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->philosopher_count)
	{
		if (pthread_create(&monitor->philosophers[i].thread, NULL,
				philosopher_routine, &monitor->philosophers[i]) != 0)
			return (1);
		usleep(10);
		i++;
	}
	return (0);
}

int	start_simulation(t_monitor *monitor)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	monitor->start_time = get_current_time();
	while (i < monitor->philosopher_count)
		monitor->philosophers[i++].last_meal_time = monitor->start_time;
	if (start_phil_threads(monitor))
	{
		printf("Failed to create philosopher thread\n");
		return (1);
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, monitor) != 0)
	{
		printf("Failed to create monitor thread\n");
		return (1);
	}
	monitor->monitor_thread = monitor_thread;
	if (join_threads(monitor, monitor_thread))
		return (1);
	return (0);
}

int	prep_dining(int argc, char **argv, t_monitor *monitor)
{
	monitor->philosopher_count = parse_positive(argv[1]);
	monitor->time_to_die = parse_positive(argv[2]);
	monitor->time_to_eat = parse_positive(argv[3]);
	monitor->time_to_sleep = parse_positive(argv[4]);
	if (argc == 6)
		monitor->required_meals = parse_positive(argv[5]);
	else
		monitor->required_meals = 0;
	monitor->end_status = false;
	pthread_mutex_init(&monitor->w_lock, NULL);
	pthread_mutex_init(&monitor->dead_lock, NULL);
	pthread_mutex_init(&monitor->meal_lock, NULL);
	initialize_forks(monitor);
	if (!monitor->forks)
		return (1);
	initialize_philosophers(monitor);
	if (!monitor->philosophers)
		return (1);
	assign_forks_to_philosophers(monitor);
	return (0);
}

int	main(int argc, char **argv)
{
	t_monitor	*monitor;

	monitor = malloc(sizeof(t_monitor));
	if (!monitor)
	{
		printf("Memory allocation for monitor failed\n");
		return (1);
	}
	memset(monitor, 0, sizeof(t_monitor));
	if (handle_args(argc, argv))
		return (free(monitor), 1);
	if (prep_dining(argc, argv, monitor))
	{
		cleanup_simulation(monitor);
		return (1);
	}
	if (start_simulation(monitor))
	{
		cleanup_simulation(monitor);
		return (1);
	}
	cleanup_simulation(monitor);
	return (0);
}
