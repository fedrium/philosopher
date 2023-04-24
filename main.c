/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyu-xian <cyu-xian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:56:11 by cyu-xian          #+#    #+#             */
/*   Updated: 2023/04/24 17:06:30 by cyu-xian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	establish(void *temp)
{
	
}

int	main(int argc, char **argv)
{
	t_rule	*rule;
	int		i;

	rule = malloc(sizeof(t_rule));
	rule->lock = malloc(sizeof(pthread_mutex_t) * 500);
	rule->con = malloc(sizeof(t_con) * 500);
	rule->philo_num = ft_atoi(argv[1]);
	rule->die_time = ft_atoi(argv[2]);
	rule->eat_time = ft_atoi(argv[3]);
	rule->sleep_time = ft_atoi (argv[4]);
	i = 0;
	while (i < rule->philo_num)
	{
		pthread_create(&rule->number, NULL, establish, &rule);
		i++;
	}
}