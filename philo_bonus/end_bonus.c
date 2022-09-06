/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:31:29 by slavoie           #+#    #+#             */
/*   Updated: 2022/09/06 14:56:22 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	drink_cigue(t_info *info)
{
	int	i;
	int	status;

	i = 0;
	while (i < info->nb_philo)
	{
		waitpid(info->philos[i].pid, &status, 0);
		sem_close(info->philos[i].die_or_eat_sem);
		i++;
	}
	free(info->philos);
	sem_close(info->message_sem);
	sem_close(info->end);
	sem_close(info->forks);
	free(info);
}

void	*out_of_food(void *void_info)
{
	t_info	*info;
	int		i;

	i = 0;
	info = void_info;
	while (i++ < info->nb_philo)
		sem_wait(info->nb_philo_finish_eat);
	sem_post(info->end);
	return (NULL);
}

void	*ares(void	*void_info)
{
	int		i;
	t_info	*info;

	i = 0;
	info = void_info;
	sem_wait(info->end);
	while (i < info->nb_philo)
		kill(info->philos[i++].pid, SIGTERM);
	return (NULL);
}

void	*charon(void *void_philo)
{
	t_philo			*philo;
	struct timeval	now;
	long long		ms;

	philo = void_philo;
	while (1)
	{
		sem_wait(philo->die_or_eat_sem);
		sem_wait(philo->info->message_sem);
		gettimeofday(&now, NULL);
		ms = convert_to_ms(now) - convert_to_ms(philo->last_meal);
		if (ms >= philo->info->time_to_die)
		{
			printf("%lld\t%d\t %s\n", convert_to_ms(now) - convert_to_ms \
			(philo->info->creat_time), philo->philo_number + 1, "died");
			sem_post(philo->info->end);
			return (NULL); 
		}
		sem_post(philo->info->message_sem);
		sem_post(philo->die_or_eat_sem);
		usleep(50);
	}
	return (NULL);
}
