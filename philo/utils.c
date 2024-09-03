/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilin <emilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:13:59 by esimpson          #+#    #+#             */
/*   Updated: 2024/09/03 11:54:32 by emilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(t_time_code time_code)
{
	struct timeval tv;

	if(gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (SECOND == time_code)
			return(tv.tv_sec + (tv.tv_usec / 1e6));
	else if(MILLISECOND == time_code)
			return((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if(MICROSECOND == time_code)
			return((tv.tv_sec * 1e6) + tv.tv_usec);
	else
			error_exit("Wrong input to gettime!");
	return(1337);				
}

void precise_usleep(long usec, t_data *table)
{
	long start;
	long elapsed;
	long rem;

	start = gettime(MICROSECOND);
	while(gettime(MICROSECOND) - start < usec)
	{
		if(simulation_finished(table))
			break;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		// to get a spinlock threshold
		if(rem > 1e3)
			usleep(rem / 2);
		else
		{
			while(gettime(MICROSECOND) - start < usec)
			;
		}		
	}
}

void	error_exit(const char *error)
{
	printf(RED "%s\n" RST, error);
	exit(EXIT_FAILURE);
}
