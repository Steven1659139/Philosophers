#include "philo.h"

void	set_info(t_info *info, char **argv)
{
	info->nb_philo = ft_atoll(argv[1]);
	info->time_to_die = ft_atoll(argv[2]);
	info->time_to_eat = ft_atoll(argv[3]);
	info->time_to_sleep = ft_atoll(argv[4]);
	if (argv[5])
		info->nb_time_each_philo_must_eat = ft_atoll(argv[5]);

}

// void	*charon(void *void_philo)
// {
// 	t_philo *philo;
// 	struct timeval	now;
// 	long long ms;

// 	philo =  void_philo;
// 	while(!philo->info->end)
// 	{

// 		// pthread_mutex_lock(&philo->info->action_mutex);
// 		pthread_mutex_lock(&philo->state_mutex);
// 		gettimeofday(&now, NULL);
// 		ms = convert_to_ms(now) - convert_to_ms(philo->last_meal);
// 		if (ms >= philo->info->time_to_die && philo->info->end == 0)
// 		{
// 			philo_message(philo, "die");
// 			philo->info->end += 1;
// 		}
// 		// pthread_mutex_unlock(&philo->info->action_mutex);
// 		pthread_mutex_unlock(&philo->state_mutex);
// 	}
// 	printf("charon take a soul\n");
// 	return (NULL);
// }
// int	is_pos_digit(char **argv)
// {
// 	int	i;
// 	int	j;

// 	i = 1;
// 	j = 0;
// 	while(argv[i])
// 	{
// 		while (argv[i][j])
// 		{
// 			if (!ft_isdigit(argv[i][j]))
// 				return(0);
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}
// 	return (1);
// }

void	corrupt_the_youth(t_info *info)
{
	pthread_t	thread;
	int			i;

	i = 0;
	gettimeofday(&info->creat_time, NULL);
	// printf("get_time\n");

	while (i < info->nb_philo)
	{
		info->philos[i].last_meal = info->creat_time;
		pthread_create(&info->philos[i].thread, NULL, do_philosopher_thing, &info->philos[i]);
		// printf("creat philo %d\n", i);
		// printf("thread philo %d creat\n", info->philos[i].philo_number);
		pthread_create(&thread, NULL, charon, &info->philos[i]);
		// printf("creat charon %d\n", i);

		// printf("thread charon %d creat\n", info->philos[i].philo_number);
		pthread_detach(thread);
		// printf("detach charon %d\n", i);
		i++;
	}

	if (info->nb_time_each_philo_must_eat)
	{
		pthread_create(&thread, NULL, out_of_food, info);
		pthread_detach(thread);
	}
	// printf("all philo creat\n");
}

void	init_philo(t_info *info)
{
	int i;

	info->philos = malloc(sizeof(t_philo) * info->nb_philo);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nb_philo);
	pthread_mutex_init(&info->action_mutex, NULL);

	if (!info->philos || !info->forks)
		yo_its_wrong("malloc failed\n", info);
	
	i = 0;

	while (i < info->nb_philo)
	{
		info->philos[i].philo_number = i + 1;
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philos[i].state_mutex, NULL);
		if (i == 0)
		{
			info->philos[i].left = &info->forks[info->nb_philo - 1];
			// printf("F%d ", info->nb_philo);
			
		}
		else
		{

			info->philos[i].left = &info->forks[i - 1];
			// printf("F%d ", i - 1);
		}
		// printf("P%d ", info->philos[i].philo_number);
		info->philos[i].right = &info->forks[i];
		info->philos[i].info = info;
		i++;
	}






}



// void	close_philo(t_info *info)
// {
// 	int		i;

// 	i = 0;
// 	while (i < info->nb_philo)
// 	{
// 		pthread_join(info->philos[i].thread, NULL);
// 		// printf("philo %d join and destroy\n", i);
// 		pthread_mutex_destroy(&info->philos[i++].state_mutex);
// 	}
// 	free(info->philos);
// 	// printf("close_philo after while\n");
// 	i = 0;
// 	while (i < info->nb_philo)
// 		pthread_mutex_destroy(&info->forks[i++]);

// 	pthread_mutex_destroy(&info->action_mutex);
// 	free(info->forks);
// 	free(info);
// }

void	morphee(t_philo *philo, long long time_to_wait)
{
	struct timeval now;
	long long	live_la;
	long long dif;

	// printf("time_to_wait = %lld\n", time_to_wait);
	while(1)
	{
		gettimeofday(&now, NULL);
		live_la = convert_to_ms(now);

		dif = live_la - convert_to_ms(philo->last_meal);
		// printf("dif = %lld time = %lld\n", dif, time_to_wait);
		if (dif >= time_to_wait)
		{
			break ;
		}
		usleep(50);
	}
}


int main(int argc, char **argv)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	// memset(&info, 0, sizeof(info));
	info->end = 0;

	if (argc != 5 && argc != 6)
	{
		yo_its_wrong("Mauvaise nombre d'argument.", info);
	}

	if (!is_pos_digit(argv))
		yo_its_wrong("Les arguments doivent être des entiers positif.", info);
	set_info(info, argv);
	init_philo(info);
	corrupt_the_youth(info);
	close_philo(info);
	return (0);
	// printf("nb_philo = %d\ntime_to_die = %d\ninfo->time_to_eat = %d\ninfo->time_to_sleep = %d\ninfo->nb_time_each_philo_must_eat = %d\n", info->nb_philo, info->time_to_die, info->time_to_eat, info->time_to_sleep, info->nb_time_each_philo_must_eat);
}