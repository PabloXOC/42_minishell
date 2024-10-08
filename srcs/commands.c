/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/10/08 21:34:44 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_com(t_info *info, int i)
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

	if (len_com(info, i) == 0)
		full_command = NULL;
	else
	{
		full_command = (char **)malloc((len_com(info, i) + 1)
				* sizeof(char *));
		if (full_command == NULL)
		{
			error_c(MALLOC_ERROR, data, info->spec);
			return (NULL);
		}
		full_command[len_com(info, i)] = NULL;
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

static int	write_in_command2(t_data *data, t_command *com, char **full_com)
{
	t_info	*info;
	int		ret;

	info = data->spec[data->sc_n]->input_info;
	ret = fill_extra_info(data, info, data->v->idx_com, com);
	if (ret == AMBIG_REDIRECT)
		return (AMBIG_REDIRECT);
	if (ret == SUCCESS)
		data->v->idx_com++;
	else
	{
		full_com[data->v->pos++]
			= ft_strdup(info->first_line_split[data->v->idx_com]);
		if (full_com[data->v->pos - 1] == NULL)
			return (error_i(MALLOC_ERROR, data));
	}
	if (data->fatal_error == true)
		return (ERROR);
	data->v->idx_com++;
	return (SUCCESS);
}

int	write_in_command(t_data *data, t_spec *spec, t_info *info, int ret)
{
	t_command	*com;
	char		**full_com;

	full_com = return_full_com(data, info, data->v->idx_com);
	if (data->fatal_error == true)
		return (MALLOC_ERROR);
	com = ft_lstnew_com(full_com);
	data->v->pos = 0;
	if (com == NULL || data->fatal_error == true)
		return (MALLOC_ERROR);
	while (info->first_line_split[data->v->idx_com] != NULL
		&& ft_strncmp(info->first_line_split[data->v->idx_com], "|", 1) != 0)
	{
		ret = write_in_command2(data, com, full_com);
		if (ret != SUCCESS)
			return (ret);
	}
	if (full_com == NULL && spec->command_list == NULL)
	{
		ft_lstdelone_com(com, &ft_free_char_pp);
		return (SUCCESS);
	}
	return (add_command_to_list(data, com, full_com));
}
