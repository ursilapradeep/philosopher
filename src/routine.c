/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:04:39 by uvadakku          #+#    #+#             */
/*   Updated: 2026/01/21 16:51:50 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	die(t_philosophers *philo)
{
	t_monitor	*monitor;

	monitor = philo->monitor;
	pthread_mutex_lock(&monitor->dead_lock);
	if (monitor->dead_flag)
	{
		pthread_mutex_unlock(&monitor->dead_lock);
		return ;
	}
	monitor->dead_flag = 1;
	pthread_mutex_unlock(&monitor->dead_lock);
	print_routine(philo, "died");
	pthread_mutex_lock(&monitor->w_lock);
	monitor->end_status = true;
	pthread_mutex_unlock(&monitor->w_lock);
}

void	dine_cycle(t_philosophers *philo, t_monitor *monitor)
{
	while (!check_if_dead(philo))
	{
		pthread_mutex_lock(&monitor->w_lock);
		if (monitor->end_status)
		{
			pthread_mutex_unlock(&monitor->w_lock);
			break ;
		}
		pthread_mutex_unlock(&monitor->w_lock);
		if (take_forks(philo) == 0)
		{
			eat(philo);
			drop_forks(philo);
			sleep_and_think(philo);
		}
		else
			sleep_ms(1);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philosophers	*philo;
	t_monitor		*monitor;

	philo = (t_philosophers *)arg;
	monitor = philo->monitor;
	if (monitor->philosopher_count == 1)
	{
		print_routine(philo, "has taken a fork");
		sleep_ms(monitor->time_to_die);
		die(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(monitor->time_to_eat * 1000);
	dine_cycle(philo, monitor);
	return (NULL);
}

int	check_if_all_ate(t_monitor *monitor)
{
	int	i;
	int	all_ate;

	if (monitor->required_meals == 0)
		return (0);
	all_ate = 1;
	i = 0;
	while (i < monitor->philosopher_count)
	{
		pthread_mutex_lock(&monitor->philosophers[i].meal_lock);
		if ((size_t)monitor->philosophers[i].meals_eaten
			< monitor->required_meals)
			all_ate = 0;
		pthread_mutex_unlock(&monitor->philosophers[i].meal_lock);
		i++;
	}
	if (all_ate)
	{
		pthread_mutex_lock(&monitor->w_lock);
		monitor->end_status = true;
		pthread_mutex_unlock(&monitor->w_lock);
	}
	return (all_ate);
}

void	*monitor_routine(void *arg)
{
	t_monitor	*monitor;
	int			i;

	monitor = (t_monitor *)arg;
	while (1)
	{
		if (check_if_all_ate(monitor))
			break ;
		i = 0;
		while (i < monitor->philosopher_count)
		{
			pthread_mutex_lock(&monitor->philosophers[i].meal_lock);
			if (is_dead(&monitor->philosophers[i], monitor->time_to_die))
			{
				pthread_mutex_unlock(&monitor->philosophers[i].meal_lock);
				return (die(&monitor->philosophers[i]), NULL);
			}
			pthread_mutex_unlock(&monitor->philosophers[i].meal_lock);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
