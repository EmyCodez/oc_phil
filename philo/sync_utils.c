/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilin <emilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:11:39 by emilin            #+#    #+#             */
/*   Updated: 2024/09/03 13:25:30 by emilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// SPINLOCK to synchronize philos start
void wait_all_threads(t_data *table)
{
    while(!get_bool(&table->table_mutex, &table->all_threads_ready))
        ;
}

