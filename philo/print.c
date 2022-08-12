#include "philo.h"

long long	convert_to_ms()
{
	struct timeval now;

	gettimeofday(&now);

	return((now.tv_sec * 1000) + (now.tv_usec / 1000));
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