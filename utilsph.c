#include "philosophers.h"

int	printer(t_info *philo, char *status)
{
	unsigned long long time;

	time = 0;
	time = ft_get_time() - philo->start;
	pthread_mutex_lock(philo->dead);
	if (*philo->deadcheck == 0)
		printf("%llu %d %s\n", time, philo->id + 1, status);
	pthread_mutex_unlock(philo->dead);
	return (0);
}

void	deadcheck(t_info *philo)
{
	unsigned long long time;
	int	i;
	int	j;
	int	result;

	i = 0;
	j = 0;
	result = 0;
	time = 0;
	while (i < philo->np)
	{
		pthread_mutex_lock(philo->dead);
		time = ft_get_time() - philo[i].lastmiam;
		if (ft_dead(philo, i, time) || pme(philo, &j, &result))
			break ;
		i++;
		pthread_mutex_unlock(philo->dead);
	}
}

int	ft_dead(t_info *philo, int i, unsigned long long time)
{
	if ((int)time > philo[i].ttd)
	{
		printf("%llu %d %s\n", time, philo->id + 1, "died");
		*philo->deadcheck = 1;
		return (1);
	}
	return (0);
}

int	pme(t_info *philo, int *j, int *result)
{
	if (philo->pme != -1)
	{
		while (*j < philo->np)
		{
			*result += philo[*j].eatcount;
			*j = *j + 1;
		}
		if (*result == philo->np * philo->pme)
		{
			*philo->deadcheck = 1;
			return (1);
		}
	}
	return (0);
}
