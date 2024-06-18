/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:44:49 by paxoc01           #+#    #+#             */
/*   Updated: 2024/06/15 20:33:19 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//initialize the data struct and variables within
t_data	*data_init(void)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof (t_data));
	if (data == NULL)
		return ((t_data *) ft_write_error_c(MALLOC_ERROR, data));
	data->paired = 0;
	data->exit = false;
	data->user = NULL;
	data->hostname = NULL;
	data->dir = NULL;
	data->entry = NULL;
	data->command_list = NULL;
	data->redirect_input = NULL;
	data->redirect_output = NULL;
	data->append_output = false;
	data->var = NULL;
	data->var_export = NULL;
	data->text_input = NULL;
	data->text_input = NULL;
	data->next_eof = NULL;
	data->malloc_error = false;
	data->input_index = 0;
	data->i = 0;
	data->j = -1;
	data->k = 0;
	data->i_ter = 0;
	data->ii = 0;
	return (data);
}

//initialize the input struct and related variables
int	init_input_struct(t_data *data)
{
	data->input_info = (t_input_var *)malloc(sizeof(t_input_var));
	if (data->input_info == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	data->input_info->first_line_ref = NULL;
	data->input_info->first_line = NULL;
	data->input_info->init_input_split = NULL;
	data->input_info->init_input = NULL;
	data->input_info->first_line_split = NULL;
	data->input_info->search_eof = NULL;
	data->input_info->terminal_input = NULL;
	data->input_info->final_text = NULL;
	data->input_info->list_eof = NULL;
	data->input_info->n_eof = 0;
	data->input_index = 0;
	data->i = 0;
	data->j = -1;
	data->k = 0;
	data->i_ter = 0;
	data->ii = 0;
	return (SUCCESS);
}
