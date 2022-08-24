/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:30:56 by slavoie           #+#    #+#             */
/*   Updated: 2022/08/22 12:30:57 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	sem_wait(philo->info->action_sem);
	gettimeofday(&now, NULL);
	ms = convert_to_ms(now) - convert_to_ms(philo->info->creat_time);
	printf("%lld\t%d\t %s\n", ms, philo->philo_number + 1, str);
	sem_post(philo->info->action_sem);
}