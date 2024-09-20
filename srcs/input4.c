/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:46:18 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/20 17:02:40 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_save_until_eof_2(t_data *data, int k, int len, int i)
{
	int	j;

	j = 0;
	while (k < len - 1)
	{
		if ((i == 1 || data->input_info_g->terminal_input[i - 1] == '\n')
			&& ft_compare_eof(&data->input_info_g->terminal_input[i],
				data->input_info_g->list_eof[j], data) == true)
		{
			i += ft_strlen(data->input_info_g->list_eof[j]) + 1;
			j++;
		}
		else
		{
			data->input_info_g->final_text[k]
				= data->input_info_g->terminal_input[i];
			i++;
			k++;
		}
	}
	data->input_info_g->final_text[k] = 0;
}

int	ft_save_until_eof(t_data *data)
{
	int	len;
	int	idx;

	len = ft_eofsize_total(data, 0, 0);
	idx = 0;
	while ((data->input_info_g->list_eof[idx]) != 0)
	{
		len -= (ft_strlen(data->input_info_g->list_eof[idx]) + 1);
		idx++;
	}
	data->input_info_g->final_text = (char *) malloc ((len) * sizeof (char));
	if (data->input_info_g->final_text == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	ft_save_until_eof_2(data, 0, len, 1);
	return (SUCCESS);
}

int	ft_len_to_eof(t_data *data, int i, int k)
{
	int	len;

	len = 0;
	while (data->input_info_g->terminal_input[i] != 0)
	{
		if ((data->input_info_g->terminal_input[i - 1] == '\n' || len == 0)
			&& ft_compare_eof_ind(&data->input_info_g->terminal_input[i],
				data->input_info_g->list_eof[k], data) == true)
			return (len);
		i++;
		len++;
	}
	return (len);
}

int	found_end_first_line(t_data *data, int i, char *input)
{
	data->input_info_g->first_line = (char *) malloc ((i + 1) * sizeof(char));
	if (data->input_info_g->first_line == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	ft_memcpy(data->input_info_g->first_line, input, i);
	data->input_info_g->first_line[i] = 0;
	data->input_info_g->terminal_input = init_terminal_input(data, input, i);
	if (data->input_info_g->terminal_input == NULL)
		return (MALLOC_ERROR);
	return (SUCCESS);
}
