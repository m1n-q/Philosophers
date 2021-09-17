/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:42:25 by mishin            #+#    #+#             */
/*   Updated: 2021/09/17 19:39:33 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define LEFT 42
# define RIGHT 24

/* linked list and input */
t_ll			*ll_new(long long data);
void			ll_push(t_ll **head, t_ll *new);
int				ll_clear(t_ll **head);
int				input_to_ll(t_ll_meta *ll, char *arg);
t_philo_meta	*ll_to_ph(t_ll_meta ll);

/* forks */
pthread_mutex_t	*make_forks(int num_philos);
int				get_fork(t_philo *philo, int direction);

/* dining philosophers */
t_philo			*make_philos(t_philo_meta *ph);
void			*dining(void *data);

/* monitoring thread */
pthread_t		*make_monitor(t_philo *philos);
void			*monitoring(void *data);

/* release */
void			*release_rscs(pthread_mutex_t *forks, struct timeval *start, t_time *lastmeals);
void			release(t_philo *philos, t_philo_meta *ph, pthread_t *monitor);

/* etc. */
int				left(t_philo *philo);
int				right(t_philo *philo);
int				last(t_philo *philo);
void			msleep(t_philo *philo);
void			slp(int ms);
double			timestamp(t_philo *philo, char *msg);
#endif
