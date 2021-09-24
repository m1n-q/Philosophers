/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:56:11 by mishin            #+#    #+#             */
/*   Updated: 2021/09/25 02:10:50 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*s1_tmp;
	const unsigned char	*s2_tmp;
	int					i;

	s1_tmp = (unsigned char *)s1;
	s2_tmp = (unsigned char *)s2;
	i = 0;
	while (s1_tmp[i] && s2_tmp[i])
	{
		if (s1_tmp[i] != s2_tmp[i])
			return (s1_tmp[i] - s2_tmp[i]);
		i++;
	}
	return (s1_tmp[i] - s2_tmp[i]);
}

static double	time_from(struct timeval *from, struct timeval *now)
{
	double			time_in_mill;

	gettimeofday(now, NULL);
	time_in_mill = (now->tv_sec - from->tv_sec) * 1000 + \
					(now->tv_usec - from->tv_usec) / 1000;
	return (time_in_mill);
}

double	timestamp(t_philo *philo, char *msg)
{
	struct timeval	now;
	double			time_in_mill;

	if (msg)
	{
		lock(philo->info->print);
		time_in_mill = time_from(philo->start, &now);
		if (philo->info->someone_died)
			return (unlock(philo->info->print));
		printf("\e[36m[%.0fms]\e[0m %d %s\n", time_in_mill, philo->id, msg);
		if (!ft_strcmp(msg, "is \e[91mdied\e[0m"))
		{
			philo->info->someone_died = philo->id;
			return (unlock(philo->info->print));
		}
		unlock(philo->info->print);
	}
	else
		time_in_mill = time_from(&philo->last_meal.time, &now);
	return (time_in_mill);
}
//NOTE: gettimeofday in timestamp() for accuracy?
//NOTE: check ft_strcmp
