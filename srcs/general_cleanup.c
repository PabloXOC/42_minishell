/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:44:52 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/07 12:48:39 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_commands(t_data *data)
{
	close_all_fds(data->command_list);
	ft_lstclear_com(&data->command_list, &ft_free_char_pp);
	data->command_list = NULL;
	data->v->idx_com = 0;
}

void	ft_free_input_info(t_data *data)
{
	if (data->input_info_g != NULL)
	{
		if (data->input_info_g->final_text != NULL)
			free(data->input_info_g->final_text);
		if (data->input_info_g->first_line != NULL)
			free(data->input_info_g->first_line);
		if (data->input_info_g->first_line_and_final_text != NULL)
			free(data->input_info_g->first_line_and_final_text);
		if (data->input_info_g->first_line_ref != NULL)
			free(data->input_info_g->first_line_ref);
		if (data->input_info_g->first_line_split != NULL)
			ft_free_char_pp(data->input_info_g->first_line_split);
		if (data->input_info_g->init_input != NULL)
			free(data->input_info_g->init_input);
		if (data->input_info_g->init_input_split != NULL)
			free(data->input_info_g->init_input_split);
		if (data->input_info_g->list_eof != NULL)
			ft_free_char_pp(data->input_info_g->list_eof);
		if (data->input_info_g->terminal_input != NULL)
			free(data->input_info_g->terminal_input);
		if (data->input_info_g->text_input != NULL)
			ft_free_char_pp(data->input_info_g->text_input);
		free(data->input_info_g);
	}
	data->input_info_g = NULL;
}

void	data_cleanup(t_data *data)
{
	delete_commands(data);
	ft_free_input_info(data);
	data->command_list = NULL;
	data->v->input_index = 0;
	data->v->stdin_cpy = 0;
	data->v->stdout_cpy = 0;
	data->v->i = 0;
	data->v->i_ter = 0;
	data->v->j = -1;
	data->v->k = 0;
	data->v->ii = 0;
	data->v->kk = 1;
	data->v->idx_com = 0;
	data->v->size = 0;
	data->v->pointer = 0;
	data->v->write_error = false;
}

void	total_cleanup(t_data *data)
{
	if (data != NULL)
	{
		delete_commands(data);
		ft_varsclear(&data->var);
		ft_varsclear(&data->var_export);
		ft_varsclear(&data->env_lst);
		ft_free_input_info(data);
		if (data->user != NULL)
			free(data->user);
		if (data->dir != NULL)
			free(data->dir);
		if (data->entry != NULL)
			free(data->entry);
		free(data);
	}
}
