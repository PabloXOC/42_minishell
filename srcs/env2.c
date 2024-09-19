/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/09/19 15:53:15 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*find_env_el(t_data *data, char *name)
{
	t_var	*node;

	node = data->env_lst;
	while (node != NULL)
	{
		if (ft_strncmp(name, node->var, ft_strlen(name) + 1) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}
