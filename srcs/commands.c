/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/06/15 20:33:52 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
int	find_command(t_data *data, t_list *full_com, char **env)
{
	char	*com;

	com = full_com->content[0];
	if (ft_strncmp(com, "echo", ft_strlen(com)) == 0)
	{
		return (SUCCESS);
	}
	if (ft_strncmp(com, "cd", ft_strlen(com)) == 0)
	{
		return (SUCCESS);
	}
	if (ft_strncmp(com, "pwd", ft_strlen(com)) == 0)
	{
		return (SUCCESS);
	}
	if (ft_strncmp(com, "export", ft_strlen(com)) == 0)
	{
		return (SUCCESS);
	}
	if (ft_strncmp(com, "unset", ft_strlen(com)) == 0)
	{
		delete_var(data, full_com->content[1]);
		return (SUCCESS);
	}
	if (ft_strncmp(com, "env", ft_strlen(com)) == 0)
		print_char_pp(env);
	if (ft_strncmp(com, "exit", ft_strlen(com)) == 0)
	{
		data->exit = true;
		return (SUCCESS);
	}
	return (INVALID_COMMAND);
}
 */

static int	length_command(t_data *data, int i)
{
	int	len;

	len = 0;
	while (data->input_info->first_line_split[i] != NULL
		&& ft_strncmp(data->input_info->first_line_split[i], "|", 1) != 0)
	{
		if (ft_strncmp(data->input_info->first_line_split[i], "<", 1) == 0)
			i++;
		else if (ft_strncmp(data->input_info->first_line_split[i], ">", 1) == 0)
			i++;
		else if (ft_strncmp(data->input_info->first_line_split[i], "<<", 2) == 0)
			i++;
		else if (ft_strncmp(data->input_info->first_line_split[i], ">>", 2) == 0)
			i++;
		else
			len++;
		i++;
	}
	return (len);
}

static int	write_in_command(t_data *data, int i)
{
	t_command	*com;
	char		**full_command;
	int			pos_command;

	full_command = (char **)malloc((length_command(data, i) + 1)*sizeof(char *));
	if (full_command == NULL)
		return (MALLOC_ERROR);
	full_command[length_command(data, i)] = NULL;
	pos_command = 0;
	while (data->input_info->first_line_split[i] != NULL
		&& ft_strncmp(data->input_info->first_line_split[i], "|", 1) != 0)
	{
		if (ft_strncmp(data->input_info->first_line_split[i], "<", 1) == 0)
			data->redirect_input = data->input_info->first_line_split[++i];
		else if (ft_strncmp(data->input_info->first_line_split[i], ">", 1) == 0)
			data->redirect_output = data->input_info->first_line_split[++i];
		else if (ft_strncmp(data->input_info->first_line_split[i], "<<", 2) == 0)
			data->limiter = data->input_info->first_line_split[++i];
		else if (ft_strncmp(data->input_info->first_line_split[i], ">>", 2) == 0)
			data->append_output = data->input_info->first_line_split[++i];
		else
			full_command[pos_command++] = ft_strdup(data->input_info->first_line_split[i]);
		if (full_command[pos_command - 1] == NULL)
			return (MALLOC_ERROR);
		i++;
	}
	if (data->command_list == NULL)
	{
		data->command_list = ft_lstnew_com(full_command);
		if (data->command_list == NULL)
			return (MALLOC_ERROR);
	}
	else
	{
		com = ft_lstnew_com(full_command);
		if (com == NULL)
			return (MALLOC_ERROR);
		ft_lstadd_back_com(&data->command_list, com);
	}
	return (i);
}

int	save_commands(t_data *data)
{
	int	i;

	i = 0;
	while (data->input_info->first_line_split[i] != NULL)
	{
		while (ft_strrchr(data->input_info->first_line_split[i], '=') != NULL)
			i++;
		i = write_in_command(data, i);
		if (data->input_info->first_line_split[i] != NULL)
			i++;
	}
}

void	delete_commands(t_data *data)
{
	data->redirect_input = NULL;
	data->redirect_output = NULL;
	data->limiter = NULL;
	data->append_output = NULL;
	ft_lstclear_com(&data->command_list, &ft_free_char_pp);
	data->command_list = NULL;
	ft_free_char_pp(data->input_info->first_line_split);
	data->input_info->first_line_split = NULL;
}
