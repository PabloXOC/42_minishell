/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec_coms2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/07/03 13:54:48 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	refresh_content_com(t_command *com, t_data *data)
{
	int	i;

	i = 0;
	if (refresh_mysignal_var(data) == MALLOC_ERROR)
		return (ERROR);
	while (com->content[i] != NULL)
	{
		com->content[i] = expand_var(data, com->content[i]);
		if (com->content[i] == NULL)
			return (ERROR);
		i++;
	}
	com->full_path = find_command_path(data->env, com->content[0], 0, data);
	if (data->fatal_error == true)
		return (ERROR);
	return (SUCCESS);
}

int	pipe_exec_coms(t_data *data, int i)
{
	int			**pipe_fd;
	t_command	*com;

	data->stdin_cpy = dup(STDIN_FILENO);
	data->stdout_cpy = dup(STDOUT_FILENO);
	com = data->command_list;
	pipe_fd = open_pipes(data);
	if (pipe_fd == NULL)
		return (ERROR);
	dup2(com->fd_in, STDIN_FILENO);
	if (refresh_content_com(com, data) == ERROR)
		return (ERROR);
	if (pipe_commands(com, data, pipe_fd, i++) == ERROR)
		return (ERROR);
	com = com->next;
	while (com != NULL)
	{
		if (refresh_content_com(com, data) == ERROR)
			return (ERROR);
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

	list_len = ft_lstsize_com(data->command_list);
	if (list_len == 1)
	{
		if (ft_command_args_errors(data->command_list->content, data) == true)
			return (SUCCESS);
		if (find_command(data, data->command_list, data->env) == INVALID_COMMAND
			&& data->fatal_error == false)
			return (pipe_exec_coms(data, 0));
		g_exit_status = 0;
	}
	if (list_len > 1)
		return (pipe_exec_coms(data, 0));
	return (SUCCESS);
}
