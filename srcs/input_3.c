/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:46:18 by pximenez          #+#    #+#             */
/*   Updated: 2024/07/01 12:06:59 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_save_until_eof_2(t_data *data, int k, int len, int i)
{
	int	j;

	j = 0;
	while (k < len - 1)
	{
		if ((i == 1 || data->input_info->terminal_input[i - 1] == '\n')
			&& ft_compare_eof(&data->input_info->terminal_input[i],
				data->input_info->list_eof[j], data) == true)
		{
			i += ft_strlen(data->input_info->list_eof[j]) + 1;
			j++;
		}
		else
		{
			data->input_info->final_text[k]
				= data->input_info->terminal_input[i];
			i++;
			k++;
		}
	}
	data->input_info->final_text[k] = 0;
}

int	ft_save_until_eof(t_data *data)
{
	int	len;
	int	j;

	len = ft_eofsize_total(data, 0, 0);
	while ((data->input_info->list_eof[j]) != 0)
	{
		len -= (ft_strlen(data->input_info->list_eof[j]) + 1);
		j++;
	}
	data->input_info->final_text = (char *) malloc ((len) * sizeof (char));
	if (data->input_info->final_text == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	ft_save_until_eof_2(data, 0, len, 1);
	return (SUCCESS);
}

int	ft_len_to_eof(t_data *data, t_input_var *input_info, int i, int k)
{
	int	len;

	len = 0;
	while (input_info->terminal_input[i] != 0)
	{
		if ((input_info->terminal_input[i - 1] == '\n' || len == 0)
			&& ft_compare_eof_ind(&input_info->terminal_input[i],
				input_info->list_eof[k], data) == true)
			return (len);
		i++;
		len++;
	}
	return (len);
}

int	ft_ask_user_for_more_input(t_data *data)
{
	char		*more_input;
	t_input_var	*info;

	info = data->input_info;
	info->init_input = ft_join_input(info->init_input, "\n");
	if (data->input_info->init_input == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	more_input = readline("> ");
	if (more_input == NULL)
		return (ft_control_d());
	info->init_input = ft_strjoin(info->init_input, more_input);
	free(more_input);
	return (SUCCESS);
}

int	ft_combine_fl_ft(t_data *data)
{
	char	*str;
	char	*str_temp;

	str_temp = ft_strdup(data->input_info->first_line);
	if (data->input_info->terminal_input != NULL
		&& data->input_info->terminal_input[0] != 0)
		str_temp = ft_join_input(str_temp, "\n");
	if (str_temp == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	str = ft_strjoin(str_temp, data->input_info->terminal_input);
	if (str == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	if (data->input_info->terminal_input != NULL
		&& data->input_info->terminal_input[0] != 0)
		str = ft_join_input(str, "\n");
	data->input_info->first_line_and_final_text = str;
	free(str_temp);
	return (SUCCESS);
}
