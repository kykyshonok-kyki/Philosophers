#include "philo.h"

static int	pars_args2(t_args *input, char **argv, int argc)
{
	if (argc == 6)
	{
		input->neat = my_atoi(argv[5]);
		if (input->neat < 1)
		{
			printf(ERROR_NEAT);
			return (1);
		}
	}
	else
		input->neat = 0;
	input->isend = 0;
	return (0);
}

static int	pars_args(t_args *input, char **argv, int argc)
{
	input->nphilos = my_atoi(argv[1]);
	if (input->nphilos < 1)
	{
		printf(ERROR_NPHILOS);
		return (1);
	}
	input->die = my_atoi(argv[2]);
	if (input->die < 1)
	{
		printf(ERROR_TIME);
		return (1);
	}
	input->eat = my_atoi(argv[3]);
	if (input->eat < 1)
	{
		printf(ERROR_TIME);
		return (1);
	}
	input->sleep = my_atoi(argv[4]);
	if (input->sleep < 1)
	{
		printf(ERROR_TIME);
		return (1);
	}
	return (pars_args2(input, argv, argc));
}

int	main(int argc, char **argv)
{
	t_args		input;
	t_philos	philos;

	if (argc != 6 && argc != 5)
	{
		printf(ERROR_OPTIONS);
		return (1);
	}
	if (pars_args(&input, argv, argc))
		return (1);
	prepare_sim(&philos, &input);
	start_sim(&philos, &input);
	end_sim(&philos, input.nphilos);
	return (0);
}
