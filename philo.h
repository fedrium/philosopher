/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyu-xian <cyu-xian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:57:00 by cyu-xian          #+#    #+#             */
/*   Updated: 2023/04/24 17:06:09 by cyu-xian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef	struct s_con {
	int	sleep;
	int	food;
	int	think;
	int	status;
}				t_con;

typedef struct s_rule {
	long long time;
	pthread_mutex_t *lock;
	int	die_time;
	int	sleep_time;
	int	eat_time;
	int	philo_num;
	pthread_t number;
	t_con *con;
}				t_rule;

long	ft_atoi(char *str);

#endif