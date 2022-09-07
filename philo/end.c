/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:09:53 by slavoie           #+#    #+#             */
/*   Updated: 2022/09/07 11:58:49 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*out_of_food(void *void_info)
{
	t_info	*info;

	info = void_info;
	while (!info->end)
	{
		pthread_mutex_lock(&info->message_mutex);
		if (info->nb_philo_finish_eat == info->nb_philo)
			info->end += 1;
		pthread_mutex_unlock(&info->message_mutex);
		usleep(50);
	}
	return (NULL);
}

void	*charon(void *void_philo)
{
	t_philo			*philo;
	struct timeval	now;
	long long		ms;

	philo = void_philo;
	while (!philo->info->end)
	{
		pthread_mutex_lock(&philo->die_or_eat_mutex);
		pthread_mutex_lock(&philo->info->message_mutex);
		gettimeofday(&now, NULL);
		ms = convert_to_ms(now) - convert_to_ms(philo->last_meal);
		if (ms >= philo->info->time_to_die && philo->info->end == 0)
		{
			printf("%lld\t%d\t %s\n", convert_to_ms(now) - convert_to_ms \
			(philo->info->creat_time), philo->philo_number, "died");
			philo->info->end += 1;
		}
		pthread_mutex_unlock(&philo->die_or_eat_mutex);
		pthread_mutex_unlock(&philo->info->message_mutex);
		usleep(50);
	}
	return (NULL);
}

void	close_philo(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_join(info->philos[i].thread, NULL);
		pthread_mutex_destroy(&info->philos[i++].die_or_eat_mutex);
	}
	free(info->philos);
	i = 0;
	while (i < info->nb_philo)
		pthread_mutex_destroy(&info->forks[i++]);
	pthread_mutex_destroy(&info->message_mutex);
	free(info->forks);
	free(info);
}
