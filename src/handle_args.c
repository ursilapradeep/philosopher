/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:58:41 by uvadakku          #+#    #+#             */
/*   Updated: 2026/01/27 11:18:47 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	parse_positive(const char *arg)
{
	size_t	result;

	result = 0;
	if (!is_positive_number(arg))
	{
		printf("Invalid input\n");
		exit(1);
	}
	while (*arg)
	{
		result = result * 10 + (*arg - '0');
		arg++;
	}
	if (result == 0 || result > INT_MAX)
	{
		printf("Invalid input\n");
		exit(1);
	}
	return ((int)result);
}

int	is_positive_number(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL || s[0] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	handle_args(int argc, char **argv)
{
	(void)argv;
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo <num_of_philo> <time_to_die>"
			"<time_to_eat> <time_to_sleep> [meals]\n");
		return (1);
	}
	return (0);
}
