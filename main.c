/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:05:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/07 19:18:42 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	* number_of_philosophers / time_to_die time_to_eat /
	 * time_to_sleep / [number_of_times_each_philosopher_must_eat]
	 */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_ll_handler	ll;
	int				i;

	i = 0;
	while (++i < argc)
		if (input_to_ll(&ll, argv[i]) == -1)
			return (1);
	if (ll.size != 3 && ll.size != 4)
		return (2);
}
