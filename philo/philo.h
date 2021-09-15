/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:42:25 by mishin            #+#    #+#             */
/*   Updated: 2021/09/15 15:58:54 by mishin           ###   ########.fr       */
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

//TODO: release all resources at exit
//NOTE: printf mutex ?
//FIXIT: clustering when num of philo is large
/* linked list and input */
t_ll			*ll_new(long long data);
void			ll_push(t_ll **head, t_ll *new);
int				ll_clear(t_ll **head);
int				input_to_ll(t_ll_meta *ll, char *arg);
void			ll_to_ph(t_ll_meta ll, t_philo_meta *ph);

/* forks */
pthread_mutex_t	*make_forks(int num_philos);
int				get_fork(t_philo *philo, int direction);

/* dining philosophers */
t_philo			*make_philos(t_philo_meta *ph);
void			*dining(void *data);

/* monitoring thread */
pthread_t		*make_monitor(t_philo *philos);
void			*monitoring(void *data);

/* atexit */
void			release_philos(t_philo *philos);
void			release_ph(t_philo_meta ph);

/* etc. */
int				left(t_philo *philo);
int				right(t_philo *philo);
int				last(t_philo *philo);
void			msleep(t_philo *philo);
void			slp(int ms);
double			timestamp(t_philo *philo, char *msg);
#endif
