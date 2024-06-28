/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/28 16:18:23 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

/* void	ft_t_clist_clear(t_clist **lst)
{
	t_clist	*next_node;

	while (*lst != NULL)
	{
		next_node = (*lst)->next;
		ft_t_clist_delone(*lst);
		(*lst) = next_node;
	}
}

void	ft_free_commands(t_data *data)
{
	if (data->temp_file != NULL)
		free(data->temp_file);
	if (data->commands != NULL)
		ft_t_clist_clear(&(commands->commands));
	if (commands != NULL)
		free(commands);
}

void	ft_cleanup(char *in_file, t_info *commands)
{
	close(commands->fd_in);
	close(commands->fd_out);
	if (commands->no_infile == 1)
		unlink(in_file);
	if (commands->no_permissions == 1)
		unlink(commands->temp_file);
	ft_free_commands(commands);
} */

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
	ft_free_input_info(data);
	//delete_commands(data);
	data->command_list = NULL;
	if (data->next_eof != NULL)
		free(data->next_eof);
	data->next_eof = NULL;
	//data->paired = 0;
	data->input_index = 0;
	data->stdin_cpy = 0;
	data->stdout_cpy = 0;
	data->i = 0;
	data->i_ter = 0;
	data->j = -1;
	data->k = 0;
	data->ii = 0;
	data->kk = 1;
	//data->kkk = 0;
	data->idx_com = 0;
	data->size = 0;
	refresh_mysignal_var(data);
	//refresh env
}

void	total_cleanup(t_data *data)
{
	ft_free_input_info(data);
	//delete_commands(data);
	ft_varsclear(&data->var);
	ft_varsclear(&data->var_export);
	ft_varsclear(&data->env_lst);
	if (data->user != NULL)
		free(data->user);
	if (data->hostname != NULL)
		free(data->hostname);
	if (data->dir != NULL)
		free(data->dir);
	if (data->entry != NULL)
		free(data->entry);
	if (data->next_eof != NULL)
		free(data->next_eof);
	free(data);
}
