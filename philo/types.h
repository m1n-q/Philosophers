/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:09:14 by mishin            #+#    #+#             */
/*   Updated: 2021/09/11 15:13:47 by mishin           ###   ########.fr       */
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

typedef struct s_philo_meta
{
	int				*num_philos;
	int				*time_to_die;
	int				*time_to_eat;
	int				*time_to_sleep;
	int				*must_eat;
}				t_philo_meta;

typedef struct s_philo
{
	struct timeval	*start;
	struct timeval	last_meal;
	t_philo_meta	*info;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eating;
	pthread_t		tid;
	int				id;
}				t_philo;

#endif
