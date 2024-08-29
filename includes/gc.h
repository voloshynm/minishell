/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:19:48 by sandre-a          #+#    #+#             */
/*   Updated: 2024/08/29 19:03:20 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <unistd.h>

typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}				t_gc;

void			*ft_malloc(t_gc **garbage, size_t size);
void			add_gc_node(t_gc **garbage, void *ptr);
void			gc(t_gc **garbage);

#endif