/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyu-xian <cyu-xian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:56:11 by cyu-xian          #+#    #+#             */
/*   Updated: 2023/05/16 17:15:08 by cyu-xian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//number_of_philosophers time_to_die /time_to_eat/time_to_sleep 
//[number_of_times_each_philosopher_must_eat]

// 1 == eat 2 == sleep 3 == think 4 == die
void	printer(t_rule *data, int index, int action)
{
	long long	time;

	pthread_mutex_lock(&data->print_lock);
	pthread_mutex_lock(&data->time_lock);
	time = get_time() - data->time;
	pthread_mutex_unlock(&data->time_lock);
	printf("[%lli] ", time);
	if (action == 1)
		printf("Philo %i is eating\n", index + 1);
	if (action == 2)
		printf("Philo %i is sleeping\n", index + 1);
	if (action == 3)
		printf("Philo %i is thinking\n", index + 1);
	if (action == 4)
	{
		printf("Philo %i is dead\n", index + 1);
		// usleep(100);
		// death(data);
	}
	pthread_mutex_unlock(&data->print_lock);
}

int	death(t_rule *data)
{
	int	i;
	
	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->number[i], 0);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->fork[i]);
		usleep(100);
		i++;
	}
	pthread_mutex_destroy(&data->index_lock);
	pthread_mutex_destroy(&data->eat_lock);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->time_lock);
	return (1);
}

void	eating(t_rule *data, int index)
{
	pthread_mutex_lock(&(data->fork[index]));
	if (index == 0)
		pthread_mutex_lock(&data->fork[data->philo_num - 1]);
	else
		pthread_mutex_lock(&data->fork[index - 1]);
	printer(data, index, 1);
	pthread_mutex_lock(&data->eat_lock);
	data->con[index].last_ate = get_time() + data->con->die_time;
	data->con[index].time_ate = data->con[index].time_ate + 1;
	pthread_mutex_unlock(&data->eat_lock);
	usleep(data->eat_time * 1000);
	if (index == 0)
		pthread_mutex_unlock(&data->fork[data->philo_num - 1]);
	else
		pthread_mutex_unlock(&data->fork[index - 1]);
	pthread_mutex_unlock(&data->fork[index]);
}

void	sleeping(t_rule *data, int index)
{
	printer(data, index, 2);
	usleep(data->sleep_time * 1000);
	printer(data, index, 3);
	// eating(data, index);
}

int	cycle(t_rule *data, int index)
{
	while (1)
	{
		pthread_mutex_lock(&data->death_lock);
		printf("dead: %i, index: %i\n", data->someone_died, index);
		if (data->someone_died == 1)
		{
			printf("owkring\n");
			break;
		}
		pthread_mutex_unlock(&data->death_lock);
		eating(data, index);
		sleeping(data, index);
		// if (data->con[index].time_ate > data->eat_time && data->eat_time != 0)
		// 	break;
	}
	return (0);
}


void	*establish(void *temp)
{
	t_rule *data;
	data = (t_rule *)temp;
	int	index;

	pthread_mutex_lock(&data->index_lock);
	index = data->index;
	pthread_mutex_unlock(&data->index_lock);
	if (index % 2 == 0)
	{
		usleep(1000);
		cycle(data, index);
	}
	else
		cycle(data, index);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rule	*rule;
	// int		i;

	(void)argc;
	rule = malloc(sizeof(t_rule)); 
	if (check(argc, argv) == 1)
	{
		printf("Argument error.\n");
		return (1);
	}
	innit_rule(rule, argv);
	thread_innit(rule);
	thread_create(rule);
	death_check(rule);
	death(rule);
	// i = 0;
	// while (i < rule->philo_num)
	// {
	// 	pthread_join(rule->number[i], 0);
	// 	usleep(100);
	// 	i++;
	// }
	return (0);
}

long long	get_time()
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_usec / 1000 + current_time.tv_sec * 1000);
}
