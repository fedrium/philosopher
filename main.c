/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyu-xian <cyu-xian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:56:11 by cyu-xian          #+#    #+#             */
/*   Updated: 2023/04/21 17:36:25 by cyu-xian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	establish(void *temp)
{
	
}

int	main(int argc, char **argv)
{
	t_rule	rule;
	int		i;

	rule.philo_num = ft_atoi(argv[1]);
	rule.die_time = ft_atoi(argv[2]);
	rule.eat_time = ft_atoi(argv[3]);
	rule.sleep_time = ft_atoi (argv[4]);
	i = 0;
	while (i < rule.philo_num)
	{
		
	}		
}