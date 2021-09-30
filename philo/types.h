/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:09:14 by mishin            #+#    #+#             */
/*   Updated: 2021/09/30 13:35:27 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_ll
{
	long long	data;
	struct s_ll	*next;
}				t_ll;

typedef struct s_ll_meta
{
	struct s_ll	*head;
	int			size;
}				t_ll_meta;

typedef struct s_time
{
	struct timeval	time;
	pthread_mutex_t	lock;
}				t_time;

typedef struct s_philo_meta
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				someone_died;
	int				philos_error;
	int				monitor_error;
	int				total_created;
	t_time			*ptr_last_meals;
	struct timeval	*start;
	pthread_mutex_t	*init;
	pthread_mutex_t	*print;
}				t_philo_meta;

typedef struct s_philo
{
	t_time			last_meal;
	t_philo_meta	*info;
	pthread_mutex_t	*forks;
	pthread_t		tid;
	int				id;
	int				terminated;
}				t_philo;

typedef struct s_init_val
{
	t_philo			*philos;
	pthread_t		*monitor;
}				t_init_val;

#endif
