/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:44:52 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/21 13:43:08 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	data_cleanup(t_data *data)
{
	ft_free_specific(data, data->spec);
	ft_free_input_info(data->input_info_g);
}

void	total_cleanup(t_data *data)
{
	if (data != NULL)
	{
		ft_varsclear(&data->var);
		ft_varsclear(&data->var_export);
		ft_varsclear(&data->env_lst);
		ft_free_specific(data, data->spec);
		ft_free_input_info(data->input_info_g);
		ft_dataclear(data);
		free(data);
	}
}
