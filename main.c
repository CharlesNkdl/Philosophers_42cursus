#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_info	*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t *death;

	if (argc != 5 && argc != 6)
		return (1);
	if (checker_args(argc, argv) == 1)
		return (1);
	philo = malloc(sizeof(t_info) * atoi(argv[1]));
	if (!philo)
		return (1);
	forks = malloc(sizeof(pthread_mutex_t) * atoi(argv[1]));
	if (!forks)
	{
		free(philo);
		return (1);
	}
	death = malloc(sizeof(pthread_mutex_t));
	if (!death)
	{
		free(philo);
		free(forks);
		return (1);
	}
	filldata(philo, argc, argv);
	fillmutex(philo,forks, death);
	joiner(philo, argv);
	ft_free(philo, forks, death);
}

void	*filldata(t_info *philo, int argc, char **argv)
{
	int	i;
	int	*deadcheck;

	deadcheck = malloc(sizeof(int));
	if (!deadcheck)
		return (NULL);
	*deadcheck = 0;
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i;
		philo[i].np = ft_atoi(argv[1]);
		philo[i].ttd = ft_atoi(argv[2]);
		philo[i].tte = ft_atoi(argv[3]);
		philo[i].tts = ft_atoi(argv[4]);
		if (argc == 6)
			philo[i].pme = ft_atoi(argv[5]);
		else
			philo[i].pme = -1;
		philo[i].lastmiam = ft_get_time();
		philo[i].start = ft_get_time();
		philo[i].eatcount = 0;
		philo[i].deadcheck = deadcheck;
		i++;
	}
	return (0);
}

void	fillmutex(t_info *philo, pthread_mutex_t *forks, pthread_mutex_t *death)
{
	int	i;

	i = 0;
	while (i < philo->np)
	{
		philo[i].left_mutex = &forks[i];
		philo[i].right_mutex = &forks[(i + 1) % philo->np];
		i++;
	}
	i = 0;
	while (i < philo->np)
	{
		pthread_mutex_init(philo[i].left_mutex, NULL);
		pthread_mutex_init(philo[i].right_mutex, NULL);
		philo[i].dead = death;
		i++;
	}
	pthread_mutex_init(philo->dead, NULL);
}
