#include "philo.h"

void	*out_of_food(void *void_info)
{
	t_info *info;

	info =  void_info;

	while (!info->end)
	{
		pthread_mutex_lock(&info->action_mutex);
		if (info->nb_philo_finish_eat == info->nb_philo)
			info->end += 1;
		pthread_mutex_unlock(&info->action_mutex);
	}
	return (NULL);
}


void	*charon(void *void_philo)
{
	t_philo *philo;
	struct timeval	now;
	long long ms;

	philo =  void_philo;
	while(!philo->info->end)
	{

		// pthread_mutex_lock(&philo->info->action_mutex);
		pthread_mutex_lock(&philo->state_mutex);
		gettimeofday(&now, NULL);
		ms = convert_to_ms(now) - convert_to_ms(philo->last_meal);
		if (ms >= philo->info->time_to_die && philo->info->end == 0)
		{
			philo_message(philo, "die");
			philo->info->end += 1;
		}
		// pthread_mutex_unlock(&philo->info->action_mutex);
		pthread_mutex_unlock(&philo->state_mutex);
	}
	// printf("charon take a soul\n");
	return (NULL);
}

void	close_philo(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_join(info->philos[i].thread, NULL);
		// printf("philo %d join and destroy\n", i);
		pthread_mutex_destroy(&info->philos[i++].state_mutex);
	}
	free(info->philos);
	// printf("close_philo after while\n");
	i = 0;
	while (i < info->nb_philo)
		pthread_mutex_destroy(&info->forks[i++]);

	pthread_mutex_destroy(&info->action_mutex);
	free(info->forks);
	free(info);
}