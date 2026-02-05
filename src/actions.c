/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:07:56 by uvadakku          #+#    #+#             */
/*   Updated: 2026/01/21 15:51:07 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	get_fork_order(t_philosophers *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

int	take_forks(t_philosophers *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	get_fork_order(philo, &first, &second);
	pthread_mutex_lock(first);
	print_routine(philo, "has taken a fork");
	if (check_if_dead(philo))
		return (pthread_mutex_unlock(first), -1);
	if (pthread_mutex_trylock(second) != 0)
	{
		pthread_mutex_unlock(first);
		usleep(100);
		return (-1);
	}
	print_routine(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

void	eat(t_philosophers *philo)
{
	print_routine(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->meal_lock);
	sleep_ms(philo->monitor->time_to_eat);
}

void	drop_forks(t_philosophers *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_and_think(t_philosophers *philo)
{
	size_t	think_time;

	print_routine(philo, "is sleeping");
	sleep_ms(philo->monitor->time_to_sleep);
	print_routine(philo, "is thinking");
	if (philo->monitor->philosopher_count % 2 == 1)
	{
		think_time = philo->monitor->time_to_eat
			* 2 - philo->monitor->time_to_sleep;
		if (think_time > 0 && think_time < 600)
			usleep(think_time * 1000);
	}
}
