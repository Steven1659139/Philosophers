/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:10:19 by slavoie           #+#    #+#             */
/*   Updated: 2022/08/22 11:10:23 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	convert_to_ms(struct timeval time)
{
	long long	ms;

	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	return (ms);
}

void	philo_message(t_philo *philo, char *str)
{
	long long		ms;
	struct timeval	now;

	pthread_mutex_lock(&philo->info->action_mutex);
	gettimeofday(&now, NULL);
	ms = convert_to_ms(now) - convert_to_ms(philo->info->creat_time);
	if (!philo->info->end)
		printf("%lld\t%d\t %s\n", ms, philo->philo_number, str);
	pthread_mutex_unlock(&philo->info->action_mutex);
}
