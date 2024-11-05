/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:44:52 by pximenez          #+#    #+#             */
/*   Updated: 2024/11/05 13:18:59 by pximenez         ###   ########.fr       */
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
		//write(1, "1\n", 2);
		//print_vars(data->var);
		ft_varsclear(&data->var);
		//write(1, "2\n", 2);
		ft_varsclear(&data->var_export);
		//write(1, "3\n", 2);
		ft_varsclear(&data->env_lst);
		//write(1, "4\n", 2);
		ft_free_specific(data, data->spec);
		//write(1, "5\n", 2);
		ft_free_input_info(data->input_info_g);
		//write(1, "6\n", 2);
		ft_dataclear(data);
		//write(1, "7\n", 2);
		free(data);
	}
}
