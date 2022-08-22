/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:31:05 by slavoie           #+#    #+#             */
/*   Updated: 2022/08/22 12:31:07 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	is_sleeping(t_philo *philo)
{
	philo_message(philo, "is sleeping");
	morphee(philo->info->time_to_sleep);
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
		eating(philo);
		is_sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
