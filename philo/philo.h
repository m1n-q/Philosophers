/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:42:25 by mishin            #+#    #+#             */
/*   Updated: 2021/09/07 20:26:23 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// memset
// printf
// malloc
// free
// write
// usleep
// gettimeofday
// pthread_create
// pthread_detach
// pthread_join
// pthread_mutex_init
// pthread_mutex_destroy
// pthread_mutex_lock
// pthread_mutex_unlock
#ifndef PHILO_H
# define PHILO_H
# include "string.h"
# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "sys/time.h"
# include "pthread.h"

# include "types.h"

# define NON_NUMERIC -4444444444LL

t_ll	*ll_new(long long data);
void	ll_push(t_ll **head, t_ll *new);
int		ll_clear(t_ll **head);
int		input_to_ll(t_ll_handler *ll, char *arg);

t_philo	*make_philos(t_philo_handler ph);
void	ll_to_ph(t_ll_handler ll, t_philo_handler *ph);
#endif
