/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec_coms2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/09/27 14:08:41 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_exec_coms(t_data *data, int i)
{
	int			**pipe_fd;
	t_command	*com;

	data->v->stdin_cpy = dup(STDIN_FILENO);
	data->v->stdout_cpy = dup(STDOUT_FILENO);
	com = data->spec[data->sc_n]->command_list;
	pipe_fd = open_pipes(data);
	if (pipe_fd == NULL)
		return (ERROR);
	dup2(com->fd_in, STDIN_FILENO);
	if (pipe_commands(com, data, pipe_fd, i++) == ERROR)
		return (ERROR);
	com = com->next;
	while (com != NULL)
	{
		if (pipe_commands(com, data, pipe_fd, i++) == ERROR)
			return (ERROR);
		com = com->next;
	}
	close_pipes(pipe_fd, data);
	return (restore_original_in_out(data));
}

int	exec_commands(t_data *data)
{
	int	list_len;
	int	status;

	list_len = ft_lstsize_com(data->spec[data->sc_n]->command_list);
	if (list_len == 1)
	{
		if (data->spec[data->sc_n]->command_list->content == NULL)
			return (SUCCESS);
		status = find_command(data,
				data->spec[data->sc_n]->command_list);
		if (status > 0 && status != INVALID_COMMAND
			&& data->fatal_error == false)
			return (SUCCESS);
		if (status == INVALID_COMMAND && data->fatal_error == false)
			return (pipe_exec_coms(data, 0));
	}
	if (list_len > 1)
	{
		return (pipe_exec_coms(data, 0));
	}
	return (SUCCESS);
}
