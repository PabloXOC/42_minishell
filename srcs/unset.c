/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/06/28 15:24:52 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_var(t_data *data, t_command *full_com)
{
	int	i;

	i = 1;
	while (full_com->content[i] != NULL)
	{
		if (ft_strncmp("?", full_com->content[i], 2) != 0)
		{
			delete_var(data, full_com->content[i], &data->var);
			delete_var(data, full_com->content[i], &data->var_export);
			delete_var(data, full_com->content[i], &data->env_lst);
		}
		i++;
	}
}
