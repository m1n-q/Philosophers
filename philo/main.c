/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:05:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/24 18:21:56 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_ll_meta		ll;
	t_philo_meta	*ph;
	t_philo			*philos;
	pthread_t		*monitor;
	int				i;

	ll.head = NULL;
	ll.size = 0;
	if (input(&ll, argc, argv) == ERROR)
		return (ERROR);
	if (make_phmeta(ll, &ph))
		return (2);
	lock(ph->start);
	philos = make_philos(ph);
	if (!philos)
		return (3);
	i = -1;
	while (++i < ph->num_philos)
		pthread_detach(philos[i].tid);
	unlock(ph->start);
	monitor = make_monitor(philos);				//TODO: if no monitor, free previous allocated rsrcs
	pthread_join(*monitor, NULL);
	usleep(200 * 1000);
	release(philos, ph, monitor);
}

//TODO: release all resources at exit

