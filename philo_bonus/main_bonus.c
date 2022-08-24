/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:31:18 by slavoie           #+#    #+#             */
/*   Updated: 2022/08/22 12:31:20 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	morphee(long long time_to_wait)
{
	struct timeval	start;
	struct timeval	now;
	long long		live_la;
	long long		ms_start;
	long long		dif;

	gettimeofday(&start, NULL);
	ms_start = convert_to_ms(start);
	while (1)
	{
		gettimeofday(&now, NULL);
		live_la = convert_to_ms(now);
		dif = live_la - ms_start;
		if (dif >= time_to_wait)
			break ;
		usleep(50);
	}
}

void	set_monitor(t_info	*info)
{
	pthread_t	thread;
	if (info->nb_time_each_philo_must_eat)
		pthread_create(&thread, NULL, out_of_food, &info);
	pthread_create(&thread, NULL, charon, &info);
}

int	main(int argc, char **argv)
{
	t_info		*info;

	info = malloc(sizeof(t_info));
	if (argc != 5 && argc != 6)
		yo_its_wrong("Mauvaise nombre d'argument.", info);
	if (!is_pos_digit(argv))
		yo_its_wrong("Les arguments doivent être des entiers positif.", info);
	set_info(info, argv);
	printf("set_info OK.\n");
	init_philo(info);
	printf("init philo OK.\n");
	corrupt_the_youth(info);
	set_monitor(info);
	drink_cigue(info);
	return (0);
}
