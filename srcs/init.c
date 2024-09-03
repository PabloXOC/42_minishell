/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:42:44 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/02 12:51:54 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_list(t_data *data)
{
	t_var	*env_list;
	char	**equality;

	env_list = data->env_lst;
	while (env_list != NULL)
	{
		if (save_export_el(data, env_list->var, env_list->content) != SUCCESS)
			return (MALLOC_ERROR);
		equality = (char **)malloc(3 * sizeof(char *));
		if (equality == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
		equality[2] = NULL;
		equality[0] = ft_strdup(env_list->var);
		equality[1] = ft_strdup(env_list->content);
		if (equality[0] == NULL || equality[1] == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
		save_var_info(data, equality, &data->var);
		env_list = env_list->next;
	}
	return (SUCCESS);
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
	data->exit = false;
	data->input_info = NULL;
	data->command_list = NULL;
	data->stdin_cpy = 0;
	data->stdout_cpy = 0;
	data->var = NULL;
	data->var_export = NULL;
	data->next_eof = NULL;
	data->fatal_error = false;
	data->write_error = false;
	data->env_lst = save_env(env);
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
	data->input_info->incomplete_input = false;
	data->input_info->text_input = NULL;
	return (SUCCESS);
}
