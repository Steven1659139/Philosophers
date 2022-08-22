/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:09:20 by slavoie           #+#    #+#             */
/*   Updated: 2022/08/22 11:09:22 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_info(t_info *info, char **argv)
{
	info->nb_philo = ft_atoll(argv[1]);
	info->time_to_die = ft_atoll(argv[2]);
	info->time_to_eat = ft_atoll(argv[3]);
	info->time_to_sleep = ft_atoll(argv[4]);
	if (argv[5])
		info->nb_time_each_philo_must_eat = ft_atoll(argv[5]);
}

void	corrupt_the_youth(t_info *info)
{
	pthread_t	thread;
	int			i;

	i = 0;
	gettimeofday(&info->creat_time, NULL);
	while (i < info->nb_philo)
	{
		info->philos[i].last_meal = info->creat_time;
		pthread_create(&info->philos[i].thread, NULL, \
		do_philosopher_thing, &info->philos[i]);
		pthread_create(&thread, NULL, charon, &info->philos[i]);
		pthread_detach(thread);
		i++;
	}
	if (info->nb_time_each_philo_must_eat)
	{
		pthread_create(&thread, NULL, out_of_food, info);
		pthread_detach(thread);
	}
}

void	init_philo(t_info *info)
{
	int	i;

	info->philos = malloc(sizeof(t_philo) * info->nb_philo);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nb_philo);
	pthread_mutex_init(&info->action_mutex, NULL);
	if (!info->philos || !info->forks)
		yo_its_wrong("malloc failed\n", info);
	i = 0;
	while (i < info->nb_philo)
	{
		info->philos[i].philo_number = i + 1;
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philos[i].state_mutex, NULL);
		if (i == 0)
			info->philos[i].left = &info->forks[info->nb_philo - 1];
		else
			info->philos[i].left = &info->forks[i - 1];
		info->philos[i].right = &info->forks[i];
		info->philos[i].info = info;
		i++;
	}
}
