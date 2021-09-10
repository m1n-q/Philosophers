/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:05:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/10 17:57:09 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	* number_of_philosophers / time_to_die time_to_eat /
	 * time_to_sleep / [number_of_times_each_philosopher_must_eat]
	 */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_ll_meta	ll;
	t_philo_meta	ph;
	t_philo			*philos;
	int				i;

	i = 0;
	ll.head = NULL;
	ll.size = 0;
	while (++i < argc)
		if (input_to_ll(&ll, argv[i]) == -1)
			return (1);
	if (ll.size != 4 && ll.size != 5)
		return (2);
	ll_to_ph(ll, &ph);

	philos = make_philos(&ph);

	if (!philos)
		return (3);
	i = -1;
	while (++i < *(ph.num_philos))
		pthread_join(philos[i].tid, NULL);

}
