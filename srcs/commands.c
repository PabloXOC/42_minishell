/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/09/23 17:27:34 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_com(t_data *data, t_info *info, int i)
{
	int	len;

	len = 0;
	while (info->first_line_split[i] != NULL
		&& ft_strncmp(info->first_line_split[i], "|", 1) != 0)
	{
		if (ft_strncmp(info->first_line_split[i], "<", 1) == 0)
			i++;
		else if (ft_strncmp(info->first_line_split[i], ">", 1) == 0)
			i++;
		else if (ft_strncmp(info->first_line_split[i], "<<",
				2) == 0)
			i++;
		else if (ft_strncmp(info->first_line_split[i], ">>",
				2) == 0)
			i++;
		else
			len++;
		i++;
	}
	return (len);
}

static char	**return_full_com(t_data *data, t_info *info, int i)
{
	char	**full_command;

	if (len_com(data, info, i) == 0)
		full_command = NULL;
	else
	{
		full_command = (char **)malloc((len_com(data, info, i) + 1)
				* sizeof(char *));
		if (full_command == NULL)
		{
			error_c(MALLOC_ERROR, data, info->spec);
			return (NULL);
		}
		full_command[len_com(data, info, i)] = NULL;
	}
	return (full_command);
}

static int	add_command_to_list(t_data *data, t_command *com,
		char **full_com)
{
	if (data->spec[data->sc_n]->command_list == NULL)
		data->spec[data->sc_n]->command_list = com;
	else
		ft_lstadd_back_com(&data->spec[data->sc_n]->command_list, com);
	if (full_com != NULL)
		data->spec[data->sc_n]->no_commands = false;
	return (SUCCESS);
}

int	write_in_command(t_data *data, t_spec *spec, t_info *info, int pos)
{
	t_command	*com;
	char		**full_com;

	full_com = return_full_com(data, info, data->v->idx_com);
	com = ft_lstnew_com(full_com);
	if (com == NULL || data->fatal_error == true)
		return (MALLOC_ERROR);
	while (info->first_line_split[data->v->idx_com] != NULL
		&& ft_strncmp(info->first_line_split[data->v->idx_com], "|", 1) != 0)
	{
		if (fill_extra_info(data, info, data->v->idx_com, com) == SUCCESS)
			data->v->idx_com++;
		else
		{
			full_com[pos++]
				= ft_strdup(info->first_line_split[data->v->idx_com]);
			if (full_com[pos - 1] == NULL)
				return (error_i(MALLOC_ERROR, data));
		}
		if (data->fatal_error == true)
			return (ERROR);
		data->v->idx_com++;
	}
	if (full_com == NULL && spec->command_list == NULL)
	{
		ft_lstdelone_com(com, &ft_free_char_pp);
		return (SUCCESS);
	}
	return (add_command_to_list(data, com, full_com));
}
