/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:42:44 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/19 15:58:46 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_input_struct(t_data *data)
{
	data->input_info_g = (t_input_var *)malloc(sizeof(t_input_var));
	if (data->input_info_g == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	data->input_info_g->first_line_ref = NULL;
	data->input_info_g->first_line = NULL;
	data->input_info_g->init_input_split = NULL;
	data->input_info_g->init_input = NULL;
	data->input_info_g->first_line_split = NULL;
	data->input_info_g->search_eof = NULL;
	data->input_info_g->terminal_input = NULL;
	data->input_info_g->final_text = NULL;
	data->input_info_g->final_text_last = NULL;
	data->input_info_g->list_eof = NULL;
	data->input_info_g->first_line_and_final_text = NULL;
	data->input_info_g->n_eof = 0;
	data->input_info_g->invalid_token = false;
	data->input_info_g->incomplete_input = false;
	data->input_info_g->text_input = NULL;
	data->control_d_g = false;
	return (SUCCESS);
}
