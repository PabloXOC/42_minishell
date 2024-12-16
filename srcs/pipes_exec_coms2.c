/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec_coms2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/11/12 13:58:42 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_father(t_data *data, t_command *com)
{
	int	status;

	waitpid(data->v->fork_id, &status, 0);
	if (g_exit_status == 260 || g_exit_status == 261)
	{
		g_exit_status = g_exit_status - 130;
		exit_codes(g_exit_status, data);
	}
	else if (com->previous_error == false)
	{
		exit_codes(WEXITSTATUS(status), data);
	}
}

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
