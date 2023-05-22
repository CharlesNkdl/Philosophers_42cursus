#include "philosophers.h"

int	init(t_info *philo, pthread_mutex_t *forks, pthread_mutex_t *death, char **argv)
{
	philo = malloc(sizeof(t_info) * atoi(argv[1]));
	if (!philo)
		return (1);
	forks = malloc(sizeof(pthread_mutex_t) * atoi(argv[1]));
	if (!forks)
		return (1);
	death = malloc(sizeof(pthread_mutex_t));
	if (!death)
		return (1);
	return (0);
}

void	*filldata(t_info *philo, int argc, char **argv)
{
	int	i;
	int	*deadcheck;
	int	nbr;

	deadcheck = malloc(sizeof(int));
	if (!deadcheck)
		return (NULL);
	*deadcheck = 0;
	i = 0;
	nbr = ft_atoi(argv[1]);
	while (i < nbr)
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

void print_data(t_info *philo, int num_philos) {
    printf("Informations sur les philosophes :\n");
    for (int i = 0; i < num_philos; i++) {
        printf("Philosophe %d :\n", i + 1);
        printf("  Identifiant : %d\n", philo[i].id);
        printf("  Nombre total de philosophes : %d\n", philo[i].np);
        printf("  Temps de mort : %d\n", philo[i].ttd);
        printf("  Temps de repas : %d\n", philo[i].tte);
        printf("  Temps de sommeil : %d\n", philo[i].tts);
        printf("  Nombre de repas max : %d\n", philo[i].pme);
        printf("  Dernier repas : %lld\n", philo[i].lastmiam);
        printf("  Temps de démarrage : %lld\n", philo[i].start);
        printf("  Compteur de repas : %d\n", philo[i].eatcount);
        printf("  Pointeur de vérification de mort : %p\n", philo[i].deadcheck);
        printf("\n");
    }
}


void	joiner(t_info *philo, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_create(&philo[i].thread, NULL, &startth, &philo[i]);
		i++;
		usleep(100);
	}
	while (*(philo->deadcheck) != 1)
		deadcheck(philo);
}

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
	usleep(100);
	//print_data(philo, philo->np);
	ft_free(philo, forks, death);
}
