/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilin <emilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:49:50 by emilin            #+#    #+#             */
/*   Updated: 2024/09/03 10:59:39 by emilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//BOOL
void set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
    safe_mutex_handle(mutex, UNLOCK);
}

bool get_bool(pthread_mutex_t *mutex, bool *value)
{
    bool ret;

    safe_mutex_handle(mutex, LOCK);
    ret = *value;
    safe_mutex_handle(mutex, UNLOCK);
    return(ret);
}

//LONG
long get_long(pthread_mutex_t *mutex, long *value)
{
    long ret;

    safe_mutex_handle(mutex, LOCK);
    ret = *value;
    safe_mutex_handle(mutex, UNLOCK);
    return(ret);
}

void set_long(pthread_mutex_t *mutex, long *dest, long value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
    safe_mutex_handle(mutex, UNLOCK);
}

bool simulation_finished(t_data *table)
{
    return(get_bool(&table->table_mutex, &table->end_simulation));
}