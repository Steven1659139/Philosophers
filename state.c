#include "philo.h"

long long	convert_to_ms(struct timeval time)
{
	long long ms;

	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;

	return(ms);
}

void	philo_message(t_philo *philo, char *str)
{
	long long		ms;
	struct timeval	now;

	pthread_mutex_lock(&philo->info->action_mutex);
	gettimeofday(&now, NULL);

	ms = convert_to_ms(now) - convert_to_ms(philo->info->creat_time);

	if (!philo->info->end)
		printf("%lld philo %d %s\n", ms, philo->philo_number, str);

	pthread_mutex_unlock(&philo->info->action_mutex);
}


void	is_sleeping(t_philo *philo)
{
	// printf("philo %d is sleeping\n", philo->philo_number);
	philo_message(philo, "is sleeping");
	usleep(philo->info->time_to_sleep * 1000);
}

// void	eating(t_philo *philo)
// {





// }

void	pick_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	// printf("philo %d taken a fork\n", philo->philo_number);
	philo_message(philo, "taken a fork");
	pthread_mutex_lock(philo->right);
	philo_message(philo, "taken a fork");
	// printf("philo %d taken a fork\n", philo->philo_number);
}

void	thinking(t_philo *philo)
{
	// printf("philo %d is thinking\n", philo->philo_number);
	philo_message(philo, "is_thinking");

	usleep(philo->info->time_to_sleep * 1000);
}

void	*do_philosopher_thing(void	*philo)
{
	pick_fork(philo);
	is_sleeping(philo);
	thinking(philo);
	return (NULL);



}
