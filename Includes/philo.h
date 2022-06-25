#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

/* Define text output */

# define ERROR_OPTIONS "ERROR! Options must be: number_of_philosophers time_to\
_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define ERROR_NPHILOS "ERROR! Option number_of_philosophers must be a \
number > 0\n"
# define ERROR_TIME "ERROR! All time options must be a number > 0. \
This number is time in milliseconds\n"
# define ERROR_NEAT "ERROR! Option number_of_times_each_philosopher_must_eat \
must be a number > 0\n"
# define END_EAT "All philosophers eat needed number of times\n"
# define ERROR_MALLOC "ERROR! Cannt malloc memory\n"

/* Define new types of structures */

typedef struct s_args
{
	int			nphilos;
	int			die;
	int			eat;
	int			sleep;
	int			neat;
	long int	start_time;
	int			isend;
}				t_args;

typedef struct s_philo
{
	int				pos;
	int				state;
	int				eatcnt;
	t_args			*input;
	long int		lasteat;
	pthread_mutex_t	*print_m;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
}				t_philo;

typedef struct s_philos
{
	t_philo			*philo;
	pthread_t		*threads;
	pthread_mutex_t	print_m;
	pthread_mutex_t	*fork_m;
}				t_philos;

/* Functions prototypes */

int			prepare_sim(t_philos *philos, t_args *input);
int			start_sim(t_philos *philos, t_args *input);
void		end_sim(t_philos *philos, int nphilos);
void		*philo_thread(void *cur);
void		print_full(pthread_mutex_t *print_m);
void		my_print(t_philo *cur);
long int	get_time(long int start_time);
void		my_sleep(int ttsleep);
int			my_atoi(char *str);

#endif
