/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/04 19:23:32 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_copy_until_eof(t_data *data, int i, int j)
{
	int		len;
	char	*str;

	len = ft_len_to_eof(data, data->kk, i);
	str = (char *) malloc ((len + 1) * sizeof (char));
	if (str == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	while (j < len)
	{
		str[j] = data->input_info_g->terminal_input[data->kk];
		j++;
		data->kk++;
	}
	str[len] = 0;
	data->input_info_g->text_input[i] = str;
	data->kk += ft_strlen(data->input_info_g->list_eof[i]) + 1;
	return (SUCCESS);
}

int	ft_individual_eof(t_data *data, int i)
{
	while (i < data->input_info_g->n_eof)
	{
		if (ft_copy_until_eof(data, i, 0) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		i++;
	}
	return (SUCCESS);
}

int	recieve_complete_input_2(t_data *data)
{
	if (ft_check_token(data, data->input_info_g) == INVALID_TOKEN)
		return (INVALID_TOKEN);
	if (ft_terminal_input(data, 0, 0) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (ft_save_until_eof(data) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (ft_individual_eof(data, 0) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (ft_combine_fl_ft(data, 0) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (ft_break_semicolons(data, 0) == MALLOC_ERROR) //to do
		return (MALLOC_ERROR);
	return (SUCCESS);
}

int	recieve_complete_input(t_data *data)
{
	t_input_var	*info;
	int			ret;

	if (init_input_struct(data) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	info = data->input_info_g;
	if (refresh_terminal_entry(data) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	info->init_input = readline(data->entry);
	if (info->init_input == NULL)
		return (ft_control_d(data));
	if (ft_empty(info->init_input) == true)
		return (EMPTY);
	data->control_d_g = false;
	//g_exit_status = 0;
	ret = first_line_complete(info->init_input, data, 0, 0);
	if (ret != SUCCESS)
		return (ret);
	if (data->input_info_g->first_line == NULL)
		return (MALLOC_ERROR);
	info->first_line_ref = ft_reformat_input(info->first_line, data);
	if (info->first_line_ref == NULL)
		return (MALLOC_ERROR);
	return (recieve_complete_input_2(data));
}
