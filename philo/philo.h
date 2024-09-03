/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilin <emilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:08:28 by esimpson          #+#    #+#             */
/*   Updated: 2024/09/03 12:13:01 by emilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

// ./philo 5 800 200 200 [5]

#define RST "\033[0m"    /* Reset to default color */
#define RED "\033[1;31m" /* Bold Red */
#define GR "\033[1;32m"
#define YL "\033[1;33m"
#define BL "\033[1;34m"
#define MG "\033[1;35m"
#define CY "\033[1;36m"
#define WH "\033[1;37m"


// PHILO STATES
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}				t_philo_status;

// OPCODE for mutex | thread functions
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

typedef	enum	e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_time_code;

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_data				*table;
}						t_philo;

struct					s_data
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				start_simulation;
	bool				end_simulation;
	bool				all_threads_ready;
	pthread_mutex_t		table_mutex;	// avoid race conditions
	pthread_mutex_t		write_mutex;
	t_fork				*forks;
	t_philo				*philos;
};

// *** FUNCTIONS ***

/* ************** utils.c *************** */
long					gettime(t_time_code time_code);
void 					precise_usleep(long usec, t_data *table);
void					error_exit(const char *error);

/* ************** parsing.c *************** */
void					parse_input(t_data *table, char **av);

/* ************** safe_functions.c *************** */
void					safe_malloc(size_t bytes);
void	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
		t_opcode opcode);

/* ************** init.c *************** */		
void	data_init(t_data *table);

/* ************** getters_setters.c *************** */
void set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool get_bool(pthread_mutex_t *mutex, bool *value);
long get_long(pthread_mutex_t *mutex, long *value);
void set_long(pthread_mutex_t *mutex, long *dest, long value);
bool simulation_finished(t_data *table);

/* ************** sync_utils.c *************** */
void wait_all_threads(t_data *table);

/* ************** dinner.c *************** */		
void *dinner_simulation(void *data);
void dinner_start(t_data *table);