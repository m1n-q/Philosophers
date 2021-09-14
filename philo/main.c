/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:05:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/14 23:38:45 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_ll_meta		ll;
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
	pthread_join(*make_monitor(philos), NULL);
	i = -1;
	while (++i < *(ph.num_philos))
		pthread_detach(philos[i].tid);
}
