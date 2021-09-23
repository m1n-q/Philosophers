/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:51:12 by mishin            #+#    #+#             */
/*   Updated: 2021/09/22 17:59:41 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char c)
{
	if (c == ' ' || \
		c == '\t' || \
		c == '\n' || \
		c == '\v' || \
		c == '\f' || \
		c == '\r')
		return (1);
	return (0);
}

static long long	atonum(const char *str, int *len)
{
	long long	ret;
	int			sign;

	ret = 0;
	sign = 1;
	if ((*str == '-' || *str == '+') && ++(*len))
		if (*str++ == '-')
			sign *= -1;
	if (!('0' <= *str && *str <= '9'))
		return (NON_NUMERIC);
	while (*str)
	{
		(*len)++;
		if ('0' <= *str && *str <= '9')
			ret = (ret * 10) + (*str - '0');
		else
		{
			(*len)--;
			break ;
		}
		str++;
	}
	if ((sign * ret) < 0)
		return (-1);
	return ((sign * ret));
}

int	input_to_ll(t_ll_meta *ll, char *arg)
{
	t_ll	*new;
	int		len;
	int		i;

	new = NULL;
	i = -1;
	while (arg[++i])
	{
		len = 0;
		if (is_space(arg[i]))
			continue ;
		if (arg[i] != '-' && arg[i] != '+' && !('0' <= arg[i] && arg[i] <= '9'))
			return (ll_clear(&(ll->head)));
		new = ll_new(atonum(arg + i, &len));
		if (!new || new->data == -1 || new->data == NON_NUMERIC)
			return (ll_clear(&(ll->head)));
		ll_push(&(ll->head), new);
		ll->size++;
		i += len - 1;
	}
	return (0);
}

t_philo_meta	*ll_to_ph(t_ll_meta ll)
{
	t_philo_meta	*ph;
	t_ll			*cur;
	int				i;

	ph = (t_philo_meta *)malloc(sizeof(t_philo_meta));
	if (!ph)
		return (NULL);
	i = 0;
	cur = ll.head;
	while (++i)
	{
		if (i == 1)
			ph->num_philos = (int)cur->data;
		else if (i == 2)
			ph->time_to_die = (int)cur->data;
		else if (i == 3)
			ph->time_to_eat = (int)cur->data;
		else if (i == 4)
			ph->time_to_sleep = (int)cur->data;
		else if (i == 5)
		{
			if (cur)
				ph->must_eat = (int)cur->data;
			else
				ph->must_eat = -1;
			break ;
		}
		cur = cur->next;
	}
	ll_clear(&ll.head);
	ph->someone_died = 0;
	return (ph);
}
