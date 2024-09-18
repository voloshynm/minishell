/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:51:49 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/05 14:52:02 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_exec
{
	char	**argv;
	char	*pathname;
}			t_exec;

int			excecute(t_exec *exec);
int			command_exists(t_exec *exec);

#endif