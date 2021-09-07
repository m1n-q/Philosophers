/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 18:45:54 by mishin            #+#    #+#             */
/*   Updated: 2021/09/07 19:16:22 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ll	*ll_new(long long data)
{
	t_ll	*ret;

	ret = (t_ll *)malloc(sizeof(t_ll));
	if (!ret)
		return (NULL);
	ret->data = data;
	ret->next = NULL;
	return (ret);
}

void	ll_push(t_ll **head, t_ll *new)
{
	t_ll	*cur;

	if (!head)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

int	ll_clear(t_ll **head)
{
	t_ll	*cur;
	t_ll	*tmp;

	if (!head)
		return (-1);
	cur = *head;
	while (cur)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	*head = NULL;
	return (-1);
}
