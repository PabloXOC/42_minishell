/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:20:50 by paxoc01           #+#    #+#             */
/*   Updated: 2024/06/18 11:59:21 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_text(t_data *data)
{
	char	*more_input;

	more_input = NULL;
	data->input_info->terminal_input = ft_join_input(data->input_info->terminal_input, "\n");
	if (data->input_info->terminal_input == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	more_input = readline("> ");
	data->input_info->terminal_input = ft_strjoin(data->input_info->terminal_input, more_input);
	free(more_input);
	return (SUCCESS);
}

//for every << we must compare the eof
int	ft_get_ter_input(t_data *data, int i, char *f_line)
{
	data->input_info->list_eof[data->k] = ft_find_eof(f_line, i + 2, data);
	if (data->input_info->list_eof[data->k] == NULL)
		return (MALLOC_ERROR);
	while (42)
	{
		while (data->input_info->terminal_input != 0
			&& data->input_info->terminal_input[data->ii] != 0)
		{
			if (data->input_info->terminal_input[data->ii] == '\n'
				&& ft_compare_eof(&data->input_info->terminal_input[data->ii + 1],
					data->input_info->list_eof[data->k], data) == true)
				return (SUCCESS);
			data->ii++;
		}
		if (ft_add_text(data) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	return (FAILURE);
}

//to make ft_terminal_input fit in 25 lines
int	ft_terminal_input_util(t_data *data, int n_single_q, int n_double_q, char *f_line)
{
	if (n_single_q % 2 == 0 && n_double_q % 2 == 0)
	{
		if (f_line[data->i_ter] == '<' && f_line[data->i_ter + 1] == '<')
		{
			if (ft_get_ter_input(data, data->i_ter, f_line) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			data->k++;
			data->i_ter += 2;
		}
	}
	return (SUCCESS);
}

//to make the terminal input from <<
int	ft_terminal_input(t_data *data, int n_single_q, int n_double_q)
{
	char	*f_line;

	f_line = data->input_info->first_line_ref;
	data->input_info->list_eof = (char **) malloc ((data->input_info->n_eof + 1) * (sizeof (char *)));
	if (data->input_info->list_eof == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	data->input_info->list_eof[data->input_info->n_eof] = 0;
	while (f_line[data->i_ter] != 0)
	{
		if (f_line[data->i_ter] == '\\' && (f_line[data->i_ter + 1] == '\''
				|| f_line[data->i_ter + 1] == '\"'))
			data->i_ter += 2;
		else if (f_line[data->i_ter] == '\'' && n_double_q % 2 == 0)
			n_single_q++;
		else if (f_line[data->i_ter] == '\"' && n_single_q % 2 == 0)
			n_double_q++;
		if (ft_terminal_input_util(data, n_single_q, n_double_q, f_line) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		data->i_ter++;
	}
	return (SUCCESS);
}
