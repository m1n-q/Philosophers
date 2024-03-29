/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:42:25 by mishin            #+#    #+#             */
/*   Updated: 2021/09/29 18:10:12 by mishin           ###   ########.fr       */
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
# define ERROR -1
# define DIED -1.0

/* linked list and input */
t_ll			*ll_new(long long data);
void			ll_push(t_ll **head, t_ll *new);
int				ll_clear(t_ll **head);
int				input_to_ll(t_ll_meta *ll, char *arg);
int				input(t_ll_meta *ll, int argc, char **argv);

/* forks */
pthread_mutex_t	*init_forks(int num_philos);
void			get_fork(t_philo *philo, int direction);

/* dining philosophers */
int				make_phmeta(t_ll_meta ll, t_philo_meta **ptr_ph);
t_philo			*make_philos(t_philo_meta *ph);
void			*dining(void *data);

/* monitoring thread */
pthread_t		*make_monitor(t_philo *philos, t_philo_meta *ph);
void			*monitoring(void *data);

/* lock (mutex) */
void			lock(pthread_mutex_t *mutex);
double			unlock(pthread_mutex_t *mutex);

/* free */
void			destroy_till(int cur_index, void *arr, char *type);
void			destroy_meta_mutex(t_philo_meta *ph);
void			free_philos(t_philo *philos);
int				free_phmeta(t_philo_meta *ph);
void			free_all(t_philo *philos, t_philo_meta *ph, pthread_t *monitor);

/* time */
double			timestamp(t_philo *philo, char *msg);
double			time_from(struct timeval *from, struct timeval *now);

/* etc. */
int				ft_strcmp(const char *s1, const char *s2);
int				left(t_philo *philo);
int				right(t_philo *philo);
int				last(t_philo *philo);
void			msleep(double ms);
int				check_terminated(t_philo *philos);

#endif
