/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/07/01 13:05:08 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_copy_until_eof(t_data *data, int i, int j)
{
	int		len;
	char	*str;

	len = ft_len_to_eof(data, data->input_info, data->kk, i);
	str = (char *) malloc ((len + 1) * sizeof (char));
	if (str == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	while (j < len)
	{
		str[j] = data->input_info->terminal_input[data->kk];
		j++;
		data->kk++;
	}
	str[len] = 0;
	data->input_info->text_input[i] = str;
	data->kk += ft_strlen(data->input_info->list_eof[i]) + 1;
	return (SUCCESS);
}

int	ft_individual_eof(t_data *data, int i)
{
	while (i < data->input_info->n_eof)
	{
		if (ft_copy_until_eof(data, i, 0) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		i++;
	}
	return (SUCCESS);
}

int	recieve_complete_input_2(t_data *data)
{
	if (ft_check_token(data) == INVALID_TOKEN)
		return (INVALID_TOKEN);
	if (ft_terminal_input(data, 0, 0) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (ft_save_until_eof(data) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (ft_individual_eof(data, 0) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (ft_combine_fl_ft(data) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

int	recieve_complete_input(t_data *data)
{
	t_input_var	*info;

	if (init_input_struct(data) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	info = data->input_info;
	if (refresh_terminal_entry(data) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	info->init_input = readline(data->entry);
	if (info->init_input == NULL)
		return (ft_control_d());
	if (ft_empty(info->init_input) == true)
		return (EMPTY);
	while (first_line_complete(info->init_input, data, 0, 0) == FAILURE)
	{
		if (ft_ask_user_for_more_input(data) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	if (data->input_info->first_line == NULL)
		return (MALLOC_ERROR);
	info->first_line_ref = ft_reformat_input(info->first_line, data);
	if (info->first_line_ref == NULL)
		return (MALLOC_ERROR);
	return (recieve_complete_input_2(data));
}
