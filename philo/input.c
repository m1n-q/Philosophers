/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:51:12 by mishin            #+#    #+#             */
/*   Updated: 2021/09/29 18:48:39 by mishin           ###   ########.fr       */
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
	if ((sign * ret) <= 0)
		return (ERROR);
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
		if (!new || new->data == ERROR || new->data == NON_NUMERIC)
			return (ll_clear(&(ll->head)));
		ll_push(&(ll->head), new);
		ll->size++;
		i += len - 1;
	}
	return (0);
}

int	input(t_ll_meta *ll, int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (input_to_ll(ll, argv[i]) == ERROR)
			return (ERROR);
	if (ll->size != 4 && ll->size != 5)
		return (ll_clear(&ll->head));
	return (0);
}
