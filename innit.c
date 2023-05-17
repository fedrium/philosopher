/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:46:30 by cyu-xian          #+#    #+#             */
/*   Updated: 2023/05/17 22:50:09 by yalee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	innit_rule(t_rule *rule, char **argv)
{
	int	i;

	i = 0;
	rule->philo_num = ft_atoi(argv[1]);
	rule->con = malloc(sizeof(t_con) * rule->philo_num);
	rule->fork = malloc(sizeof(pthread_mutex_t) * rule->philo_num);
	rule->die_time = ft_atoi(argv[2]);
	rule->number = malloc(sizeof(pthread_t) * rule->philo_num);
	rule->eat_time = ft_atoi(argv[3]);
	rule->sleep_time = ft_atoi (argv[4]);
	rule->con->last_ate = get_time();
	if (argv[5] != 0)
		rule->full_time = ft_atoi(argv[5]);
	rule->index = 0;
	rule->someone_died = 0;
	rule->ate_num = 0;
	while (i < rule->philo_num)
		rule->con[i++].time_ate = 0;
}

void	thread_innit(t_rule *rule)
{
	int	i;

	i = 0;
	while (i < rule->philo_num)
	{
		pthread_mutex_init(&rule->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&rule->index_lock, NULL);
	pthread_mutex_init(&rule->eat_lock, NULL);
	pthread_mutex_init(&rule->print_lock, NULL);
	pthread_mutex_init(&rule->time_lock, NULL);
	pthread_mutex_init(&rule->death_lock, NULL);
	pthread_mutex_init(&rule->counter_lock, NULL);
	pthread_mutex_lock(&rule->time_lock);
	rule->time = get_time();
	pthread_mutex_unlock(&rule->time_lock);
}

void	thread_create(t_rule *rule)
{
	while (rule->index < rule->philo_num)
	{
		pthread_create(&rule->number[rule->index], NULL, (void *) establish, (void *) rule);
		usleep(100);
		pthread_mutex_lock(&rule->index_lock);
		pthread_mutex_lock(&rule->eat_lock);
		rule->con[rule->index].last_ate = get_time();
		rule->index++;
		pthread_mutex_unlock(&rule->eat_lock);
		pthread_mutex_unlock(&rule->index_lock);
	}
}

void	death_check(t_rule *rule)
{
	int	i;
	int	is_dead;
	
	is_dead = 0;
	i = 0;
	while (!is_dead)
	{
		if (i == rule->philo_num)
			i = 0;
		pthread_mutex_lock(&rule->eat_lock);
		if (rule->con[i].last_ate < (get_time() - (long long)rule->die_time))
		{
			is_dead = 1;
			pthread_mutex_lock(&rule->death_lock);
			rule->someone_died = 1;
			pthread_mutex_unlock(&rule->death_lock);
			printer(rule, i, 4);
		}
		pthread_mutex_unlock(&rule->eat_lock);
		pthread_mutex_lock(&rule->counter_lock);
		if (rule->ate_num == rule->philo_num)
		{
			is_dead = 1;
			pthread_mutex_lock(&rule->death_lock);
			rule->someone_died = 1;
			pthread_mutex_unlock(&rule->death_lock);
			printer(rule, i, 5);
		}
		pthread_mutex_unlock(&rule->counter_lock);
		i++;
	}
	// death(rule);
}

int	check(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}