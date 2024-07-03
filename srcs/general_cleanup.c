/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:44:52 by pximenez          #+#    #+#             */
/*   Updated: 2024/07/03 17:44:54 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_commands(t_data *data)
{
	close_all_fds(data->command_list);
	ft_lstclear_com(&data->command_list, &ft_free_char_pp);
	data->command_list = NULL;
	data->idx_com = 0;
}

void	ft_free_input_info(t_data *data)
{
	if (data->input_info != NULL)
	{
		if (data->input_info->final_text != NULL)
			free(data->input_info->final_text);
		if (data->input_info->first_line != NULL)
			free(data->input_info->first_line);
		if (data->input_info->first_line_and_final_text != NULL)
			free(data->input_info->first_line_and_final_text);
		if (data->input_info->first_line_ref != NULL)
			free(data->input_info->first_line_ref);
		if (data->input_info->first_line_split != NULL)
			ft_free_char_pp(data->input_info->first_line_split);
		if (data->input_info->init_input != NULL)
			free(data->input_info->init_input);
		if (data->input_info->init_input_split != NULL)
			free(data->input_info->init_input_split);
		if (data->input_info->list_eof != NULL)
			ft_free_char_pp(data->input_info->list_eof);
		if (data->input_info->terminal_input != NULL)
			free(data->input_info->terminal_input);
		if (data->input_info->text_input != NULL)
			ft_free_char_pp(data->input_info->text_input);
		free(data->input_info);
	}
	data->input_info = NULL;
}

void	data_cleanup(t_data *data)
{
	delete_commands(data);
	ft_free_input_info(data);
	data->command_list = NULL;
	if (data->next_eof != NULL)
		free(data->next_eof);
	data->next_eof = NULL;
	data->input_index = 0;
	data->stdin_cpy = 0;
	data->stdout_cpy = 0;
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
		if (data->next_eof != NULL)
			free(data->next_eof);
		free(data);
	}
}
