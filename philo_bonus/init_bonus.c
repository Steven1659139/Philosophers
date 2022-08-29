/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:30:45 by slavoie           #+#    #+#             */
/*   Updated: 2022/08/22 12:30:48 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_info(t_info *info, char **argv)
{
	if (info->nb_philo < 1)
		yo_its_wrong("Il doit y avoir au moins 1 philosophe.\n", info);
	if (info->time_to_die < 0 || info->time_to_eat < 0 || info->time_to_sleep < 0)
		yo_its_wrong("Aucun temps ne peut être inférieur à 0.\n", info);
	if (argv[5])
		if (info->nb_time_each_philo_must_eat < 1)
			yo_its_wrong("Les philosophes ne peuvent pas manger moins de 1 fois.\n", info);
}

void	set_info(t_info *info, char **argv)
{
	info->nb_philo = atoi(argv[1]);
	info->time_to_die = atoi(argv[2]);
	info->time_to_eat = atoi(argv[3]);
	info->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		info->nb_time_each_philo_must_eat = atoi(argv[5]);
	check_info(info, argv);
	// printf("nb_philo = %d\ndie = %lld\neat = %lld\nsleep = %lld\n", info->nb_philo, info->time_to_die, info->time_to_eat, info->time_to_sleep );
}

sem_t	*sem_start(const char *name, unsigned int value)
{
	sem_t *sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem != SEM_FAILED)
		return (sem);
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

void	init_philo(t_info *info)
{
	long long	i;
	char	*name;
	char	*number;

	i = 0;
	info->philos = ft_calloc(info->nb_philo, sizeof(t_philo *));
	if (!info->philos)
		yo_its_wrong("Error: Malloc failed.", info);
	info->end = sem_start("end", 0);
	info->action_sem = sem_start("action", 1);
	info->forks = sem_start("fork", info->nb_philo);
	info->nb_philo_finish_eat = sem_start("nb_finish_eat", 0);

	// info->end = sem_open("end", O_CREAT | O_EXCL, 0644, 0);
	// info->action_sem = sem_open("action", O_CREAT | O_EXCL, 0644, 1);


	// info->forks = sem_open("fork", O_CREAT | O_EXCL, 0644, info->nb_philo);
	// info->nb_philo_finish_eat = sem_open("nb_meal", O_CREAT | O_EXCL, 0644, 0);
	// printf("sem OK.\n");

	while (i < info->nb_philo)
	{
		number = ft_itoa(i + 1);
		name = ft_strjoin("philo ", number);
		info->philos[i].state_sem = sem_start(name, 1);
		info->philos[i].philo_number = i;
		info->philos[i].info = info;
		i++;
		// free(name);
		// free(number);
	}
}

void	corrupt_the_youth(t_info *info)
{
	int			i;

	gettimeofday(&info->creat_time, NULL);
	i = 0;
	while (i < info->nb_philo)
	{
		info->philos[i].last_meal = info->creat_time;
		info->philos[i].pid = fork();
		// printf("pid = %d\n", info->philos[i].pid);
		if (info->philos[i].pid == 0)
			return (do_philosopher_thing(&info->philos[i]));
		else if (info->philos[i].pid < 0)
		{
			yo_its_wrong("Error: your philosopher took a fork in the knee.\n", info);
			exit(0);
		}
		i++;
	}
}