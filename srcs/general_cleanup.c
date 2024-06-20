/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/06/19 17:03:58 by farah            ###   ########.fr       */
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
			free(data->input_info->first_line_split);
		if (data->input_info->init_input != NULL)
			free(data->input_info->init_input);
		if (data->input_info->init_input_split != NULL)
			free(data->input_info->init_input_split);
		ft_free_char_pp(data->input_info->list_eof);
		if (data->input_info->terminal_input != NULL)
			free(data->input_info->terminal_input);
		free(data->input_info);
	}
	data->input_info = NULL;
}

void data_cleanup(t_data *data)
{
	ft_free_input_info(data);
	delete_commands(data);
	if (data->fd_in > 0)
		close(data->fd_in);
	if (data->fd_out > 0)
		close(data->fd_out);
	data->fd_in = 0;
	data->fd_out = 0;
	data->next_eof = NULL;
	if (data->text_input != NULL)
		free(data->text_input);
	data->text_input = NULL;
	data->i = 0;
	data->j = -1;
	data->k = 0;
	data->i_ter = 0;
	data->ii = 0;
}

void total_cleanup(t_data *data)
{
	//delete all vars
	//delete all
	ft_free_input_info(data);
	delete_commands(data);
	if (data->fd_in > 0)
		close(data->fd_in);
	if (data->fd_out > 0)
		close(data->fd_out);
	data->next_eof = NULL;
	if (data->text_input != NULL)
		free(data->text_input);
	data->text_input = NULL;
	free(data);
}
