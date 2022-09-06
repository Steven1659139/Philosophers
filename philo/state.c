/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:09:29 by slavoie           #+#    #+#             */
/*   Updated: 2022/09/06 14:56:12 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_sleeping(t_philo *philo)
{
	philo_message(philo, "is sleeping");
	morphee(philo->info->time_to_sleep);
}

void	pick_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->cue);
	pthread_mutex_lock(philo->left);
	philo_message(philo, "has taken fork");
	if (philo->info->nb_philo == 1)
	{
		morphee(philo->info->time_to_die);
		return ;
	}
	pthread_mutex_lock(philo->right);
	philo_message(philo, "has taken fork");
	pthread_mutex_unlock(&philo->cue);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->die_or_eat_mutex);
	gettimeofday(&philo->last_meal, NULL);
	if (!philo->info->end)
		philo_message(philo, "is eating");
	philo->nb_eat += 1;
	if (philo->nb_eat == philo->info->nb_time_each_philo_must_eat)
		philo->info->nb_philo_finish_eat += 1;
	morphee(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&philo->die_or_eat_mutex);
}

void	thinking(t_philo *philo)
{
	philo_message(philo, "is_thinking");
}

void	*do_philosopher_thing(void	*philo_void)
{
	t_philo	*philo;

	philo = philo_void;
	if (philo->philo_number % 2 == 0)
		morphee(philo->info->time_to_eat);
	while (!philo->info->end)
	{
		pick_fork(philo);
		if (philo->info->nb_philo != 1)
		{
			eating(philo);
			is_sleeping(philo);
			thinking(philo);
		}
		else
			break ;
	}
	return (NULL);
}
