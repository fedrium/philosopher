/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:56:11 by cyu-xian          #+#    #+#             */
/*   Updated: 2023/05/09 18:11:04 by yalee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//number_of_philosophers time_to_die /time_to_eat/time_to_sleep [number_of_times_each_philosopher_must_eat]

void	eating(t_rule *data, int index)
{
	pthread_mutex_lock(&(data->fork[index]));
	if (index == 0)
		pthread_mutex_lock(&data->fork[data->philo_num - 1]);
	else
		pthread_mutex_lock(&data->fork[index - 1]);
	printf("philo %i is eating\n", index);
	//eat
	usleep(data->eat_time * 1000);
	pthread_mutex_unlock(&data->fork[index]);
	if (index == 0)
		pthread_mutex_unlock(&data->fork[data->philo_num - 1]);
	else
		pthread_mutex_unlock(&(data->fork[index - 1]));
	sleeping(data, index);
	
}

void	sleeping(t_rule *data, int index)
{
	printf("philo %i is sleeping\n", index);
	usleep(data->sleep_time * 1000);
	printf("philo %i is thinking\n", index);
	eating(data, index);
}

void	*establish(void *temp)
{
	t_rule *data;
	data = (t_rule *)temp;
	int	index;

	index = data->index;

	while (!data->time) {}
	if (index % 2 == 1)
		usleep(data->die_time * 1000 / 2);
	eating(data, index);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rule	*rule;
	int		i;
	// pthread_mutex_t *forks;

	(void)argc;
	rule = malloc(sizeof(t_rule));
	rule->con = malloc(sizeof(t_con) * 100);
	rule->philo_num = ft_atoi(argv[1]);
	rule->fork = malloc(sizeof(pthread_mutex_t) * rule->philo_num);
	rule->die_time = ft_atoi(argv[2]);
	rule->number = malloc(sizeof(pthread_t) * rule->philo_num);
	rule->eat_time = ft_atoi(argv[3]);
	rule->sleep_time = ft_atoi (argv[4]);
	if (argv[5] != 0)
		rule->full_time = ft_atoi(argv[5]);
	rule->index = 0;
	i = 0;
	while (i < rule->philo_num)
	{
		pthread_mutex_init(&rule->fork[i], NULL);
		i++;
	}
	while (rule->index < rule->philo_num)
	{
		pthread_create(&rule->number[rule->index], NULL, (void *) establish, (void *) rule);
		usleep(1000);
		rule->index++;
	}
	rule->time = get_time();
	i = 0;
	while (i < rule->philo_num - 1)
	{
		pthread_join(rule->number[i], 0);
		i++;
	}
	return (0);
}

long long	get_time()
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_usec + current_time.tv_sec * 1000);
}

void	philos_init(char **argv, t_rule **philos, pthread_mutex_t )
{
	int	total;
	int	i;

	total = ft_atoi(argv[1]);
	i = 0;
	while (i < total)
	{
		philos[i]->index = i + 1;
		// time = get_time();
	}
}

void	forks_init(pthread_mutex_t **forks, int num)
{
	int	i;

	i = 0;
	while(i < num)
	{
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
}

// int main(int argc, char **argv)
// {
// 	t_rule	*philos;
// 	pthread_mutex_t	*forks;
	
// 	if (argc < 5 || argc > 6)
// 	{
// 		printf("Invalid number of arguements!\n");
// 		return (0);
// 	}
// 	// check of valid args
// 	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
// 	forks_init(&forks, ft_atoi(argv[1]));
// 	philos = malloc(sizeof(t_rule) * ft_atoi(argv[1]));
// 	philos_init(argv, &philos, &);
// }