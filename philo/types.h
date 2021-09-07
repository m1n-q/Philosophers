/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:09:14 by mishin            #+#    #+#             */
/*   Updated: 2021/09/07 19:36:29 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_ll
{
	long long	data;
	struct s_ll	*next;
}				t_ll;

typedef struct s_ll_handler
{
	struct s_ll	*head;
	int			size;
}				t_ll_handler;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		tid;
}				t_philo;

typedef struct s_philo_handler
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	must_eat;
}				t_philo_handler;

#endif
