/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyu-xian <cyu-xian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:57:00 by cyu-xian          #+#    #+#             */
/*   Updated: 2023/05/09 17:04:46 by cyu-xian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef	struct s_con {
	int	slept;
	long long last_ate;
	int	thinked;
	int	status;
}				t_con;

typedef struct s_rule {
	int	index;
	long long time;
	pthread_mutex_t *fork;
	int	die_time;
	int	sleep_time;
	int	eat_time;
	int	philo_num;
	int full_time;
	pthread_t *number;
	t_con *con;
}				t_rule;

long		ft_atoi(char *str);
void		sleeping(t_rule *data, int index);
void		eating(t_rule *data, int index);
void		forks_init(pthread_mutex_t **forks, int num);
long long	get_time();

#endif