/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:22:25 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/22 22:53:12 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* The ft_lstadd_front function adds a new node at the beginning of a list.
*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new)
	{
		new->prev = NULL;
		new->next = *lst;
		(*lst) = new;
	}
}
