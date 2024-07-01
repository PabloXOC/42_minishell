/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:20:50 by paxoc01           #+#    #+#             */
/*   Updated: 2024/07/01 13:52:43 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_text(t_data *data, t_input_var *info)
{
	char	*more_input;
	char	*temp;

	more_input = NULL;
	info->terminal_input = ft_join_input(info->terminal_input, "\n");
	if (data->input_info->terminal_input == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	more_input = readline("> ");
	if (more_input == NULL)
		return (ft_control_d());
	temp = ft_strjoin(info->terminal_input, more_input);
	if (info->terminal_input != NULL)
		free(data->input_info->terminal_input);
	data->input_info->terminal_input = temp;
	free(more_input);
	return (SUCCESS);
}

//for every << we must compare the eof
int	ft_get_ter_input(t_data *data, t_input_var *info, int i, char *f_line)
{
	info->list_eof[data->k] = ft_find_eof(f_line, i + 2, data);
	if (info->list_eof[data->k] == NULL)
		return (MALLOC_ERROR);
	while (42)
	{
		while (info->terminal_input != 0 && info->terminal_input[data->ii] != 0)
		{
			if (info->terminal_input[data->ii] == '\n'
				&& ft_compare_eof(&info->terminal_input[data->ii + 1],
					info->list_eof[data->k], data) == true)
				return (SUCCESS);
			data->ii++;
		}
		if (ft_add_text(data, info) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	return (FAILURE);
}

//to make ft_terminal_input fit in 25 lines
int	ft_terminal_input_util(t_data *data, int s_q, int d_q, char *f_line)
{
	if (s_q % 2 == 0 && d_q % 2 == 0)
	{
		if (f_line[data->i_ter] == '<' && f_line[data->i_ter + 1] == '<')
		{
			if (ft_get_ter_input(data, data->input_info,
					data->i_ter, f_line) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			data->k++;
			data->i_ter += 2;
		}
	}
	return (SUCCESS);
}

int	ft_malloc_eof(t_data *data, t_input_var *info)
{
	info->list_eof = (char **) malloc ((info->n_eof + 1) * (sizeof (char *)));
	if (info->list_eof == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	info->text_input = (char **) malloc ((info->n_eof + 1) * (sizeof (char *)));
	if (info->text_input == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	info->list_eof[info->n_eof] = 0;
	info->text_input[info->n_eof] = 0;
	return (SUCCESS);
}

//to make the terminal input from <<
int	ft_terminal_input(t_data *data, int s_q, int d_q)
{
	char	*f_line;

	f_line = data->input_info->first_line_ref;
	if (ft_malloc_eof(data, data->input_info) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	while (f_line[data->i_ter] != 0)
	{
		if (f_line[data->i_ter] == '\\' && (f_line[data->i_ter + 1] == '\''
				|| f_line[data->i_ter + 1] == '\"'))
			data->i_ter += 2;
		else if (f_line[data->i_ter] == '\'' && d_q % 2 == 0)
			s_q++;
		else if (f_line[data->i_ter] == '\"' && s_q % 2 == 0)
			d_q++;
		if (ft_terminal_input_util(data, s_q, d_q, f_line) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		data->i_ter++;
	}
	return (SUCCESS);
}
