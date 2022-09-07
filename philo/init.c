/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:09:20 by slavoie           #+#    #+#             */
/*   Updated: 2022/09/07 11:58:44 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_info(t_info *info, char **argv)
{
	if (info->nb_philo < 1)
		return (yo_its_wrong("Il doit y avoir au moins 1 philosophe.\n", info));
	if (info->time_to_die < 0 || info->time_to_eat < 0 \
	|| info->time_to_sleep < 0)
		return (yo_its_wrong("Aucun temps ne peut être inférieur à 0.\n", info));
	if (argv[5])
		if (info->nb_time_each_philo_must_eat < \
		1)
			return (yo_its_wrong \
			("Les philosophes ne peuvent pas manger moins de 1 fois.\n", info));
	return (1);
}

int	set_info(t_info *info, char **argv)
{
	info->end = 0;
	info->nb_philo_finish_eat = 0;
	info->nb_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info->nb_time_each_philo_must_eat = ft_atoi(argv[5]);
	return (check_info(info, argv));
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
	pthread_mutex_init(&info->message_mutex, NULL);
	if (!info->philos || !info->forks)
		yo_its_wrong("malloc failed\n", info);
	i = 0;
	while (i < info->nb_philo)
	{
		info->philos[i].philo_number = i + 1;
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philos[i].die_or_eat_mutex, NULL);
		pthread_mutex_init(&info->philos[i].cue, NULL);
		if (i == 0)
			info->philos[i].left = &info->forks[info->nb_philo - 1];
		else
			info->philos[i].left = &info->forks[i - 1];
		info->philos[i].right = &info->forks[i];
		info->philos[i].info = info;
		i++;
	}
}
