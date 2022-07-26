/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:31:05 by slavoie           #+#    #+#             */
/*   Updated: 2022/09/06 14:56:43 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pick_fork(t_philo *philo)
{
	sem_wait(philo->info->forks);
	philo_message(philo, "has taken a fork.");
	sem_wait(philo->info->forks);
	philo_message(philo, "has taken a fork.");
}

void	is_sleeping(t_philo *philo)
{
	philo_message(philo, "is sleeping");
	morphee(philo->info->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	philo_message(philo, "is_thinking");
}

void	eating(t_philo *philo)
{
	sem_wait(philo->die_or_eat_sem);
	gettimeofday(&philo->last_meal, NULL);
	philo_message(philo, "is eating.");
	philo->nb_eat += 1;
	if (philo->nb_eat == philo->info->nb_time_each_philo_must_eat)
		sem_post(philo->info->nb_philo_finish_eat);
	morphee(philo->info->time_to_eat);
	sem_post(philo->die_or_eat_sem);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

void	do_philosopher_thing(void	*philo_void)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = philo_void;
	pthread_create(&thread, NULL, charon, philo);
	if (philo->philo_number % 2 == 0)
		morphee(philo->info->time_to_eat);
	while (1)
	{
		pick_fork(philo);
		eating(philo);
		is_sleeping(philo);
		thinking(philo);
	}
	exit(0);
}
