/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:31:29 by slavoie           #+#    #+#             */
/*   Updated: 2022/08/22 12:31:30 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	drink_cigue(t_info *info)
{
	int	i;
	int status;

	i = 0;
	while (i < info->nb_philo)
	{
		waitpid(info->philos[i].pid, &status, 0);
		sem_close(info->philos[i].state_sem);
	}
	free(info->philos);
	sem_close(info->action_sem);
	sem_close(info->end);
	sem_close(info->forks);
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

void	*charon(void *void_philo)
{
	t_philo			*philo;
	struct timeval	now;
	long long		ms;

	philo = void_philo;
	while (!philo->info->end)
	{
		sem_wait(philo->state_sem);
		gettimeofday(&now, NULL);
		ms = convert_to_ms(now) - convert_to_ms(philo->last_meal);
		if (ms >= philo->info->time_to_die)
		{
			philo_message(philo, "die");
			sem_post(philo->info->end);
			return (NULL);
		}
		sem_post(philo->state_sem);
	}
	return (NULL);
}