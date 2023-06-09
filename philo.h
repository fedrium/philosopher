/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:57:00 by cyu-xian          #+#    #+#             */
/*   Updated: 2023/05/17 22:24:02 by yalee            ###   ########.fr       */
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
	int	is_full;
}				t_con;

typedef struct s_rule {
	int	index;
	long long time;
	pthread_mutex_t *fork;
	pthread_mutex_t index_lock;
	pthread_mutex_t eat_lock;
	pthread_mutex_t time_lock;
	pthread_mutex_t print_lock;
	pthread_mutex_t death_lock;
	pthread_mutex_t counter_lock;
	int	die_time;
	int	sleep_time;
	int	eat_time;
	int	philo_num;
	int full_time;
	int	someone_died;
	int	ate_num;
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
void		death(t_rule *data);
void		innit_rule(t_rule *rule, char **argv);
void		thread_innit(t_rule *rule);
void		thread_create(t_rule *rule);
void		*establish(void *temp);
void		death_check(t_rule *rule);
void		full_check(t_rule *rule, int i);
int			ft_isdigit(int c);
int			check(int argc, char **argv);
int			life_check(t_rule *data, int index);

#endif