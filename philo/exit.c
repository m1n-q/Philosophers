/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 13:57:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/16 01:59:34 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* *********************** */
/*                         */
/*   reclaimed resources   */
/*                         */
/*	- philo & meta         */
/*	- mutex (fork)         */
/*	- mutex (meal)         */
/*	- timeval (start)      */
/*	- t_time (meal)        */
/*	- forks                */
/*		                   */
/*	- linked list          */
/*	- monitor (joined)     */
/*	- threads (detached)   */
/* *********************** */

/*


  19: 	ret = (t_ll *)malloc(sizeof(t_ll));

  45: 	monitor = (pthread_t *)malloc(sizeof(pthread_t));

  24: 	philos = (t_philo *)malloc(sizeof(t_philo) * *(ph->num_philos));
  {
	30: 	start = (struct timeval *)malloc(sizeof(struct timeval));
	19: 	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philos);
	33: 	last_meals = (t_time *)malloc(sizeof(t_time) * *(ph->num_philos));
  }

*/

void	release_philos(t_philo *philos)
{
	// int	num_philos;
	int	i;

	printf("%p\n", philos);
	// num_philos = *(philos[0].info->num_philos);
	// printf("===============> %d\n", num_philos);
	i = -1;
	// while (++i < num_philos)
	// {
	// 	// pthread_mutex_destroy(&philos[0].forks[i]);
	// 	// pthread_mutex_destroy(&philos[i].last_meal.lock);
	// }
	// free(philos[0].forks);
	// free(philos[0].start);
	// free(philos);
}

void	release_ph(t_philo_meta ph)
{
	free(ph.num_philos);
	free(ph.time_to_die);
	free(ph.time_to_eat);
	free(ph.time_to_sleep);
	free(ph.must_eat);
	free(ph.last_meals);

}
