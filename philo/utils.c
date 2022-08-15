#include "philo.h"

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
				return(0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

long long	ft_atoll(const char *str)
{
	long long	n;
	int			negation;

	n = 0;
	negation = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '+' || *str == '-')
	{
		if (n >= 1)
			return (0);
		if (*str == '-')
			negation++;
		n++;
		str++;
	}
	n = 0;
	if (*str == '+' && negation > 0)
		return (n);
	while (*str >= '0' && *str <= '9')
		n = n * 10 + *str++ - '0';
	if (negation)
		n *= -1;
	return (n);
}