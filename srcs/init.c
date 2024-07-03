/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/03 16:45:01 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_list(t_data *data)
{
	t_var	*env_list;

	env_list = data->env_lst;
	while (env_list != NULL)
	{
		save_export_el(data, env_list->var, env_list->content);
		env_list = env_list->next;
	}
}

static void	init_idx(t_data *data)
{
	data->input_index = 0;
	data->i = 0;
	data->i_ter = 0;
	data->j = -1;
	data->k = 0;
	data->ii = 0;
	data->kk = 1;
	data->idx_com = 0;
	data->size = 0;
	data->pointer = 0;
}

t_data	*data_init(char **env)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof (t_data));
	if (data == NULL)
		return ((t_data *) ft_write_error_c(MALLOC_ERROR, data));
	data->user = NULL;
	data->dir = NULL;
	data->entry = NULL;
	data->env = env;
	data->env_lst = safe_env(env);
	data->exit = false;
	data->input_info = NULL;
	data->command_list = NULL;
	data->stdin_cpy = 0;
	data->stdout_cpy = 0;
	data->var = NULL;
	data->var_export = NULL;
	data->next_eof = NULL;
	data->fatal_error = false;
	init_idx(data);
	export_list(data);
	return (data);
}

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
	data->input_info->final_text_last = NULL;
	data->input_info->list_eof = NULL;
	data->input_info->first_line_and_final_text = NULL;
	data->input_info->n_eof = 0;
	data->input_info->invalid_token = false;
	data->input_info->text_input = NULL;
	return (SUCCESS);
}
