/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilin <emilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:07:44 by esimpson          #+#    #+#             */
/*   Updated: 2024/08/31 12:08:57 by emilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data table;

	if (5 == argc || 6 == argc)
	{
		// 1) errors check
		parse_input(&table, argv);

		// 2) create
		data_init(&table);

		// 3) start simulation
		dinner_start(&table);

		// 4) No leaks -> philos full or 1 philo died
		clean(&table);
	}
	else
	{
		error_exit("Wrong input:\n" GR "Correct is ./philo 5 800 200 200 [5]" RST);
	}
}