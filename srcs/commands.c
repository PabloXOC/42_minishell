/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/07/01 13:43:01 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_command(t_data *data, t_command *full_com, char **env)
{
	char	*com;

	com = full_com->content[0];
	if (ft_strncmp(com, "cd", ft_strlen(com)) == 0)
		return (change_dir(data, full_com));
	if (ft_strncmp(com, "export", ft_strlen(com)) == 0)
	{
		if (full_com->content[1] == NULL)
			print_export(data);
		else
			export_var(data, full_com, &data->var);
		return (SUCCESS);
	}
	if (ft_strncmp(com, "unset", ft_strlen(com)) == 0)
		return (unset_var(data, full_com));
	if (ft_strncmp(com, "env", ft_strlen(com)) == 0)
		return (print_env(data));
	if (ft_strncmp(com, "exit", ft_strlen(com)) == 0)
	{
		data->exit = true;
		return (SUCCESS);
	}
	return (INVALID_COMMAND);
}

static int	len_com(t_data *data, int i)
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
		else if (ft_strncmp(data->input_info->first_line_split[i], "<<",
				2) == 0)
			i++;
		else if (ft_strncmp(data->input_info->first_line_split[i], ">>",
				2) == 0)
			i++;
		else
			len++;
		i++;
	}
	return (len);
}

static char	**return_full_com(t_data *data, int i)
{
	char	**full_command;

	if (len_com(data, i) == 0)
		full_command = NULL;
	else
	{
		full_command = (char **)malloc((len_com(data, i) + 1) * sizeof(char *));
		if (full_command == NULL)
		{
			ft_write_error_c(MALLOC_ERROR, data);
			return (NULL);
		}
		full_command[len_com(data, i)] = NULL;
	}
	return (full_command);
}

static int	add_command_to_list(t_data *data, t_command *com, int i,
		char **full_com)
{
	if (data->command_list == NULL)
		data->command_list = com;
	else
		ft_lstadd_back_com(&data->command_list, com);
	data->idx_com = i;
	if (full_com == NULL)
		return (NO_COMMANDS);
	return (SUCCESS);
}

static int	write_in_command(t_data *data, t_input_var *info)
{
	t_command	*com;
	char		**full_com;
	int			pos;
	int			i;

	i = data->idx_com;
	full_com = return_full_com(data, i);
	com = ft_lstnew_com(full_com);
	if (com == NULL)
		return (MALLOC_ERROR);
	pos = 0;
	while (info->first_line_split[i] != NULL
		&& ft_strncmp(info->first_line_split[i], "|", 1) != 0)
	{
		if (fill_extra_info(data, i, com) == SUCCESS)
			i++;
		else
		{
			full_com[pos++] = ft_strdup(info->first_line_split[i]);
			if (full_com[pos - 1] == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
		}
		i++;
	}
	return (add_command_to_list(data, com, i, full_com));
}

void	path_commands(t_data *data)
{
	int			i;
	t_command	*com;

	com = data->command_list;
	while (com != NULL)
	{
		i = 0;
		com->full_path = ft_find_command_path(data->env, com->content[i++], 0);
		while (com->content[i] != NULL)
		{
			com->content[i] = expand_var(data, com->content[i]);
			i++;
		}
		com = com->next;
	}
}

int	save_pipelines(t_data *data, t_input_var *info)
{
	int	i;

	if (data->input_info->first_line_split == NULL)
		return (0);
	while (data->input_info->first_line_split[data->idx_com] != NULL)
	{
		if (ft_there_is_equal(info->first_line_split[data->idx_com]) == true
			&& ft_isspecial(info->first_line_split[data->idx_com]) == false
			&& ft_starts_with_number(info->first_line_split[data->idx_com])
			== false)
			data->idx_com++;
		else
		{
			while (data->input_info->first_line_split[data->idx_com] != NULL)
			{
				if (write_in_command(data, data->input_info) == NO_COMMANDS)
					return (NO_COMMANDS);
				if (data->input_info->first_line_split[data->idx_com] != NULL)
					data->idx_com++;
			}
		}
	}
	path_commands(data);
	//print_commands(data);
	return (SUCCESS);
}

void	print_commands(t_data *data)
{
	t_command	*com;

	com = data->command_list;
	while (com != NULL)
	{
		if (com->content != NULL)
			print_char_pp(com->content);
		ft_printf("full path: %s\n", com->full_path);
		ft_printf("text input: %s\n", com->text_input);
		ft_printf("red input: %s\n", com->redirect_input);
		ft_printf("red output: %s\n", com->redirect_output);
		ft_printf("fd in: %i\n", com->fd_in);
		ft_printf("fd out: %i\n", com->fd_out);
		ft_printf("temp file: %s\n", com->temp_file);
		com = com->next;
	}
}
