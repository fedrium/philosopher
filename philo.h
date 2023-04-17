/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyu-xian <cyu-xian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:57:00 by cyu-xian          #+#    #+#             */
/*   Updated: 2023/04/17 16:11:57 by cyu-xian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO

#include <stdio.h>
#include <pthread.h>

typedef	struct s_con {
	int	sleep;
	int	food;
	int	think;
	int	status;
}				t_con;

#endif