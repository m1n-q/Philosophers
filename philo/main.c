/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:05:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/16 02:33:45 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_ll_meta		ll;
	t_philo_meta	ph;
	t_philo			*philos;
	int				exit;
	int				i;

	i = 0;
	exit = 1;
	ll.head = NULL;
	ll.size = 0;
	while (++i < argc)
		if (input_to_ll(&ll, argv[i]) == -1)
			return (1);
	if (ll.size != 4 && ll.size != 5)
		return (2);
	ll_to_ph(ll, &ph);
	ll_clear(&ll.head);
	philos = make_philos(&ph);
	printf("=========> threadid = %p |\n=========> philos=%p |\n=========> main.c: %d\n", pthread_self(), philos, *(philos[0].info->time_to_eat));
	if (!philos)
		return (3);
	i = -1;
	while (++i < *(ph.num_philos))
		pthread_detach(philos[i].tid);
	pthread_join(*make_monitor(philos), (void *)&exit);
	printf("=========> threadid = %p |\n=========> philos=%p |\n=========> main.c\n", pthread_self(), philos);
	// printf("main.c: %d\n", *(philos[0].info->time_to_eat));		//ISSUE: ACCESSING PHILOS CAUSES SEGFAULT AFTER PTHREAD_JOIN

	// if (exit == 0)
	// {
	// 	sleep(3);
	// 	// release_philos(philos);
	// 	release_ph(ph);
	// }
}
