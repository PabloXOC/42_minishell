/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec_coms2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/07/04 20:07:39 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_char_pp(char **stack)
{
	int	len;

	if (stack == NULL)
		return (0);
	len = 0;
	while (stack[len] != 0)
		len++;
	return (len);
}

static char	**create_new_char_pp(char **content, char **new_content,
		t_data *data, int i)
{
	int		len;
	int		len_new;
	char	**new_stack;
	int		pos;

	if (content == NULL || new_content == NULL)
		return ((char **)ft_write_error_c(MALLOC_ERROR, data));
	len = len_char_pp(content);
	len_new = len_char_pp(new_content);
	new_stack = (char **)malloc((len + len_new) * sizeof(char *));
	if (new_stack == NULL)
		return ((char **)ft_write_error_c(MALLOC_ERROR, data));
	new_stack[len + len_new - 1] = NULL;
	pos = 0;
	while (pos < i)
	{
		new_stack[pos] = ft_strdup(content[pos]);
		pos++;
	}
	i = 0;
	while (new_content[i] != 0)
		new_stack[pos++] = ft_strdup(new_content[i++]);
	while (content[pos - i + 1] != 0)
	{
		new_stack[pos] = ft_strdup(content[pos - i + 1]);
		pos++;
	}
	ft_free_char_pp(content);
	ft_free_char_pp(new_content);
	return (new_stack);
}

int	refresh_content_com(t_command *com, t_data *data)
{
	int	i;

	i = 0;
	if (refresh_mysignal_var(data) == MALLOC_ERROR)
		return (ERROR);
	while (com->content[i] != NULL)
	{
		if (com->content[i][0] != '$')
		{
			com->content[i] = expand_var(data, com->content[i]);
			if (com->content[i] == NULL)
				return (ERROR);
		}
		else
		{
			com->content[i] = expand_var(data, com->content[i]);
			if (com->content[i] == NULL)
				return (ERROR);
			com->content = create_new_char_pp(com->content, ft_split(com->content[i], 32), data, i);
		}
		i++;
	}
	print_char_pp(com->content);
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