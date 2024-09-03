/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilin <emilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:17:58 by emilin            #+#    #+#             */
/*   Updated: 2024/09/03 11:43:13 by emilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *dinner_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    wait_all_threads(philo->table);

    while(!simulation_finished(philo->table))
    {
        if(philo->full)
            break;
        eat(philo);
        sleeping();
        thinking(philo);
    }
    return(NULL);
}

void dinner_start(t_data *table)
{
    int i;

    i = -1;
    if(0 == table->nbr_limit_meals)
        return;
    else if( 1 == table->philo_nbr)
        ;
    else
    {
        while( ++i < table->philo_nbr)
            safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
             &table->philos[i], CREATE);
    }
    // start of simulation
    table->start_simulation = gettime(MILLISECOND);
    // all threads ready!
    set_bool(&table->table_mutex, &table->all_threads_ready, true);
    i = -1;
    while( ++i < table->philo_nbr)
        safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
}