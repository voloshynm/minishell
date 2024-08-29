/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:09:52 by sandre-a          #+#    #+#             */
/*   Updated: 2024/08/29 19:19:45 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	add_gc_node(t_gc **garbage, void *ptr)
{
	t_gc	*new_node;
	t_gc	*current;

	if (!ptr)
		return ;
	new_node = malloc(sizeof(t_gc));
	if (!new_node)
	{
		free(ptr);
		write(1, "Memory allocation failed! Stopping Process", 42);
		exit(EXIT_FAILURE);
	}
	new_node->ptr = ptr;
	new_node->next = NULL;
	if (*garbage == NULL)
		*garbage = new_node;
	else
	{
		current = *garbage;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	*ft_malloc(t_gc **garbage, size_t size)
{
	void	*ptr;
	t_gc	*new_node;

	ptr = malloc(size);
	if (!ptr)
	{
		write(1, "Memory allocation failed! Stopping Process", 42);
		exit(EXIT_FAILURE);
	}
	add_gc_node(garbage, new_node);
	return (ptr);
}

void	gc(t_gc **garbage)
{
	t_gc	*current;
	t_gc	*next_node;

	if (*garbage == NULL)
		return ;
	current = *garbage;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->ptr);
		free(current);
		current = next_node;
	}
	*garbage = NULL;
}
