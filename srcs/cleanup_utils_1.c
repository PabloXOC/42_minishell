/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:40:58 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/20 12:22:20 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fds(t_command *command)
{
	t_command	*com;

	com = command;
	while (com != NULL)
	{
		if (com->fd_in > 2)
			close(com->fd_in);
		if (com->fd_out > 2)
			close(com->fd_out);
		if (com->temp_file != NULL)
		{
			unlink(com->temp_file);
			free(com->temp_file);
			com->temp_file = NULL;
		}
		com = com->next;
	}
}

void	ft_free_commands(t_data *data, t_command *com)
{
	close_all_fds(com);
	ft_lstclear_com(&com, &ft_free_char_pp);
	com = NULL;
	data->v->idx_com = 0;
}

void	ft_free_specific(t_data *data, t_specific **specific)
{
	int	i;

	i = 0;
	while (i <= data->n_semicolons)
	{
		ft_free_commands(data, specific[i]->command_list);
		ft_free_input_info(specific[i]->input_info);
		if (specific[i]->next_eof != NULL)
			free(specific[i]->next_eof);
		free(specific[i]);
		i++;
	}
	if (specific != NULL)
		free(specific);
}

void    ft_dataclear(t_data *data)
{
	if (data->user != NULL)
		free(data->user);
	if (data->dir != NULL)
		free(data->dir);
	if (data->entry != NULL)
		free(data->entry);
	if (data->v != NULL)
		free(data->v);
}