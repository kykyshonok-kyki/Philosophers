#include "philo.h"

static void	check_sim_end(t_philos *philos, t_args *input)
{
	int			i;
	long int	cur_time;
	int			full_cnt;

	while (!input->isend)
	{
		full_cnt = 0;
		i = -1;
		while (++i < input->nphilos && !input->isend)
		{
			cur_time = get_time(input->start_time);
			if (philos->philo[i].lasteat + input->die < cur_time)
				philos->philo[i].state = -1;
			if (philos->philo[i].state == -1)
				input->isend = -1;
			if (input->neat && philos->philo[i].eatcnt >= input->neat)
				full_cnt++;
		}
		if (full_cnt == input->nphilos)
			input->isend = 1;
	}
	if (input->isend == -1)
		my_print(&philos->philo[--i]);
	else
		print_full(&philos->print_m);
}

int	prepare_sim(t_philos *philos, t_args *input)
{
	int	i;

	philos->threads = malloc(sizeof(pthread_t) * input->nphilos);
	philos->fork_m = malloc(sizeof(pthread_mutex_t) * input->nphilos);
	philos->philo = malloc(sizeof(t_philo) * input->nphilos);
	if (!philos->philo || !philos->fork_m || !philos->threads)
	{
		printf(ERROR_MALLOC);
		return (1);
	}
	pthread_mutex_init(&philos->print_m, NULL);
	i = 0;
	while (i < input->nphilos)
	{
		pthread_mutex_init(&philos->fork_m[i], NULL);
		i++;
	}
	return (0);
}

static int	start_pthreads(t_philos *philos, t_args *input)
{
	int	i;

	i = 0;
	while (i < input->nphilos)
	{
		if (pthread_create(&philos->threads[i], NULL, philo_thread,
				&philos->philo[i]))
			return (1);
		pthread_detach(philos->threads[i]);
		i += 2;
	}
	usleep(2000);
	i = 1;
	while (i < input->nphilos)
	{
		if (pthread_create(&philos->threads[i], NULL, philo_thread,
				&philos->philo[i]))
			return (1);
		pthread_detach(philos->threads[i]);
		i += 2;
	}
	check_sim_end(philos, input);
	return (0);
}

int	start_sim(t_philos *philos, t_args *input)
{
	int		i;

	i = 0;
	input->start_time = get_time(0);
	while (i < input->nphilos)
	{
		philos->philo[i].pos = i;
		philos->philo[i].state = 0;
		philos->philo[i].eatcnt = 0;
		philos->philo[i].input = input;
		philos->philo[i].lasteat = 0;
		philos->philo[i].print_m = &philos->print_m;
		if (i == 0)
			philos->philo[i].lfork = &philos->fork_m[input->nphilos - 1];
		else
			philos->philo[i].lfork = &philos->fork_m[i - 1];
		philos->philo[i].rfork = &philos->fork_m[i];
		i++;
	}
	return (start_pthreads(philos, input));
}

void	end_sim(t_philos *philos, int nphilos)
{
	int	i;

	i = 0;
	while (i < nphilos)
	{
		pthread_mutex_destroy(&philos->fork_m[i]);
		i++;
	}
	free(philos->threads);
	free(philos->fork_m);
	free(philos->philo);
	pthread_mutex_destroy(&philos->print_m);
}
