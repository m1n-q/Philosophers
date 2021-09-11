/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:42:25 by mishin            #+#    #+#             */
/*   Updated: 2021/09/11 15:15:04 by mishin           ###   ########.fr       */
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
# define LEFT 42
# define RIGHT 24

t_ll			*ll_new(long long data);
void			ll_push(t_ll **head, t_ll *new);
int				ll_clear(t_ll **head);
int				input_to_ll(t_ll_meta *ll, char *arg);
void			ll_to_ph(t_ll_meta ll, t_philo_meta *ph);

pthread_mutex_t	*make_forks(int num_philos);
pthread_mutex_t	*make_eating(int num_philos);
int				get_fork(t_philo *philo, int direction);


t_philo			*make_philos(t_philo_meta *ph);
double			timestamp(t_philo *philo, char *msg);
pthread_t		*make_monitor(t_philo *philos);
void			*monitoring(void *data);

int				left(t_philo *philo);
int				right(t_philo *philo);
void			eat(t_philo *philo);
int				last(t_philo *philo);
void			msleep(t_philo *philo);
#endif
