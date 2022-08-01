#include "philo.h"

void	set_info(t_info *info, char **argv)
{
	info->nb_philo = atoi(argv[1]);
	info->time_to_die = atoi(argv[2]);
	info->time_to_eat = atoi(argv[3]);
	info->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		info->nb_time_each_philo_must_eat = atoi(argv[5]);

}

int	is_pos_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while(argv[i])
	{
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("Les arguments doivent être des entiers positif.");
				exit(0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void	create_philo(t_info *info)
{
	// pthread_t	thread;
	int			i;

	i = 1;
	// gettimeofday(&info->creat_time, NULL);

	while (i <= info->nb_philo)
	{
		// info->philos[i].last_meal = info->creat_time;
		pthread_create(&info->philos[i].thread, NULL, do_philosopher_thing, &info->philos[i]);
		i++;
	}
}

void	init_philo(t_info *info)
{
	int i;

	info->philos = malloc(sizeof(t_philo) * info->nb_philo);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nb_philo);

	if (!info->philos || !info->forks)
		printf("malloc failed\n");
	
	i = 1;

	while (i <= info->nb_philo)
	{
		info->philos[i].philo_number = i;
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philos[i].state_mutex, NULL);
		if (i == 1)
		{
			info->philos[i].left = &info->forks[info->nb_philo];
			printf("F%d ", info->nb_philo);
			
		}
		else
		{

			info->philos[i].left = &info->forks[i - 1];
			printf("F%d ", i - 1);
		}
		printf("P%d ", info->philos[i].philo_number);
		i++;
	}






}


int main(int argc, char **argv)
{
	t_info	*info;

	// memset(&info, 0, sizeof(info));
	info = malloc(sizeof(t_info));

	if (argc != 5 && argc != 6)
	{
		printf("Mauvaise nombre d'argument");
		exit(0);
	}
	is_pos_digit(argv);
	set_info(info, argv);
	init_philo(info);
	// create_philo(info);
	// printf("nb_philo = %d\ntime_to_die = %d\ninfo->time_to_eat = %d\ninfo->time_to_sleep = %d\ninfo->nb_time_each_philo_must_eat = %d\n", info->nb_philo, info->time_to_die, info->time_to_eat, info->time_to_sleep, info->nb_time_each_philo_must_eat);






}