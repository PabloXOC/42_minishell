/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/07/03 12:50:38 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	add_command_to_list(t_data *data, t_command *com,
		char **full_com)
{
	if (data->command_list == NULL)
		data->command_list = com;
	else
		ft_lstadd_back_com(&data->command_list, com);
	if (full_com == NULL)
		return (NO_COMMANDS);
	return (SUCCESS);
}

int	write_in_command(t_data *data, t_input_var *info)
{
	t_command	*com;
	char		**full_com;
	int			pos;

	full_com = return_full_com(data, data->idx_com);
	com = ft_lstnew_com(full_com);
	if (com == NULL || data->fatal_error == true)
		return (MALLOC_ERROR);
	pos = 0;
	while (info->first_line_split[data->idx_com] != NULL
		&& ft_strncmp(info->first_line_split[data->idx_com], "|", 1) != 0)
	{
		if (fill_extra_info(data, data->idx_com, com) == SUCCESS)
			data->idx_com++;
		else
		{
			full_com[pos++] = ft_strdup(info->first_line_split[data->idx_com]);
			if (full_com[pos - 1] == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
		}
		if (data->fatal_error == true)
			return (ERROR);
		data->idx_com++;
	}
	return (add_command_to_list(data, com, full_com));
}
