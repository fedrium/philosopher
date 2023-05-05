/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyu-xian <cyu-xian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:56:11 by cyu-xian          #+#    #+#             */
/*   Updated: 2023/05/03 16:00:47 by cyu-xian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//number_of_philosophers time_to_die /time_to_eat/time_to_sleep [number_of_times_each_philosopher_must_eat]

void	*establish(void *temp)
{
	t_rule *data;
	struct timeval current_time;
	
	data = (t_rule *)temp;
	gettimeofday(&current_time, NULL);
	data->time = current_time.tv_usec;
	
	return (0);
}

int	main(int argc, char **argv)
{
	t_rule	*rule;
	int		i;

	(void)argc;
	rule = malloc(sizeof(t_rule));
	rule->lock = malloc(sizeof(pthread_mutex_t) * 500);
	rule->con = malloc(sizeof(t_con) * 500);
	rule->philo_num = ft_atoi(argv[1]);
	rule->die_time = ft_atoi(argv[2]);
	rule->number = malloc(sizeof(pthread_t) * rule->philo_num);
	rule->eat_time = ft_atoi(argv[3]);
	rule->sleep_time = ft_atoi (argv[4]);
	if (argv[5] != 0)
		rule->full_time = ft_atoi(argv[5]);
	i = 0;
	while (i < rule->philo_num)
	{
		pthread_create(&rule->number[i], NULL, (void *) establish, (void *) rule);
		i++;
	}
	i = 0;
	while (i < rule->philo_num)
	{
		pthread_join(rule->number[i], 0);
		i++;
	}
	return (0);
}