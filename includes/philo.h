/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:17:07 by uvadakku          #+#    #+#             */
/*   Updated: 2026/01/21 16:51:18 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <ctype.h>

typedef struct s_monitor
{
	struct s_philosophers	*philosophers;
	pthread_t				monitor_thread;
	pthread_mutex_t			w_lock;
	pthread_mutex_t			dead_lock;
	pthread_mutex_t			meal_lock;
	pthread_mutex_t			*forks;
	int						philosopher_count;
	int						dead_flag;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	size_t					required_meals;
	size_t					start_time;
	bool					end_status;

}	t_monitor;

typedef struct s_philosophers
{
	pthread_t				thread;
	pthread_mutex_t			dead_lock;
	pthread_mutex_t			meal_lock;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	struct s_monitor		*monitor;
	int						id;
	long					last_meal_time;
	int						meals_eaten;
	int						meals_required;
}	t_philosophers;

size_t		parse_positive(const char *arg);
int			handle_args(int argc, char **argv);
int			is_positive_number(const char *s);
void		initialize_forks(t_monitor *monitor);
void		initialize_philosophers(t_monitor *monitor);
void		*monitor_routine(void *arg);
void		*philosopher_routine(void *arg);
int			check_if_all_ate(t_monitor *monitor);
void		assign_forks_to_philosophers(t_monitor *monitor);
int			start_simulation(t_monitor *monitor);
int			start_phil_threads(t_monitor *monitor);
int			initialize_shared_mutexes(t_monitor *monitor);
int			join_threads(t_monitor *monitor, pthread_t monitor_thread);

/* time utils */
long		get_current_time(void);
void		sleep_ms(unsigned int ms);
void		print_current_time_in_millisecond(void);

/* utils */
int			is_dead(t_philosophers *philo, size_t time_to_die);
int			check_if_dead(t_philosophers *philo);
void		print_routine(t_philosophers *philo, const char *action);

/* actions */
int			take_forks(t_philosophers *philo);
void		eat(t_philosophers *philo);
void		drop_forks(t_philosophers *philo);
void		sleep_and_think(t_philosophers *philo);
void		dine_cycle(t_philosophers *philo, t_monitor *monitor);
void		get_fork_order(t_philosophers *philo, pthread_mutex_t **first,
				pthread_mutex_t **second);

/* death */
void		die(t_philosophers *philo);
void		cleanup_simulation(t_monitor *monitor);

#endif