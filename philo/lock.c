/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:32:45 by mishin            #+#    #+#             */
/*   Updated: 2021/09/24 17:37:46 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock(pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
}

double	unlock(pthread_mutex_t *mutex)
{
	pthread_mutex_unlock(mutex);
	return (DIED);
}
