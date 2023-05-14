/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyu-xian <cyu-xian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:57:00 by cyu-xian          #+#    #+#             */
/*   Updated: 2023/05/14 15:21:34 by cyu-xian         ###   ########.fr       */
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
	long long die_time;
	int time_ate;
}				t_con;

typedef struct s_rule {
	int	index;
	long long time;
	pthread_mutex_t *fork;
	pthread_mutex_t index_lock;
	pthread_mutex_t eat_lock;
	pthread_mutex_t time_lock;
	pthread_mutex_t print_lock;
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
void		condition(t_rule *data, int index, char chars);
void		printer(t_rule *data, int index, int action);
int			death(t_rule *data);

#endif