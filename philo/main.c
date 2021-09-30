/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:05:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/30 15:26:23 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_init_val	init(t_philo_meta *ph)
{
	t_init_val	init_val;
	int			i;

	lock(ph->init);
	init_val.philos = make_philos(ph);
	if (!init_val.philos)
		return ((t_init_val){NULL, NULL});
	init_val.monitor = make_monitor(init_val.philos, ph);
	if (!init_val.monitor)
		return ((t_init_val){NULL, NULL});
	i = -1;
	while (++i < ph->num_philos)
		pthread_detach(init_val.philos[i].tid);
	unlock(ph->init);
	return (init_val);
}

int	main(int argc, char **argv)
{
	t_ll_meta		ll;
	t_philo_meta	*ph;
	t_init_val		init_val;

	ll.head = NULL;
	ll.size = 0;
	if (input(&ll, argc, argv) == ERROR)
		return (1);
	if (make_phmeta(ll, &ph) == ERROR)
		return (2);
	init_val = init(ph);
	if (!init_val.philos && !init_val.monitor)
		return (3);
	pthread_join(*(init_val.monitor), NULL);
	if (check_terminated(init_val.philos))
		free_all(init_val.philos, ph, init_val.monitor);
}

//TODO: free all resources at exit
//TODO: test check_termintated, malloc error, create error
//TODO: leaks, large case, fsanitize=address&pthread, norminette
