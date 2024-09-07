/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:42:44 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/07 12:45:46 by paxoc01          ###   ########.fr       */
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

void	ft_reset_vars(t_data *data)
{
	data->v->input_index = 0;
	data->v->i = 0;
	data->v->i_ter = 0;
	data->v->j = -1;
	data->v->k = 0;
	data->v->ii = 0;
	data->v->kk = 1;
	data->v->idx_com = 0;
	data->v->size = 0;
	data->v->pointer = 0;
	data->v->stdin_cpy = 0;
	data->v->stdout_cpy = 0;
	data->v->stdin_cpy = STDIN_FILENO;
	data->v->stdout_cpy = STDOUT_FILENO;
	data->v->fork_id = 0;
	data->v->quote = 0;
	data->v->write_error = false;
}

t_data	*data_init(char **env)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof (t_data));
	if (data == NULL)
		return ((t_data *) ft_write_error_c(MALLOC_ERROR, data, NULL));
	data->user = NULL;
	data->dir = NULL;
	data->entry = NULL;
	data->env = env;
	data->exit = false;
	data->command_list = NULL;
	
	data->var = NULL;
	data->var_export = NULL;
	//data->next_eof = NULL;
	data->fatal_error = false;
	//data->write_error = false;
	data->env_lst = save_env(env);
	data->v = NULL;
	data->v = (t_intervar *) malloc (sizeof (t_intervar));
	if (data->v == NULL)
		return ((t_data *) ft_write_error_c(MALLOC_ERROR, data, NULL));
	ft_reset_vars(data);
	export_list(data);
	return (data);
}

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
