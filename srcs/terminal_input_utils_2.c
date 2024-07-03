/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_input_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:41:15 by pximenez          #+#    #+#             */
/*   Updated: 2024/07/03 17:41:41 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_control_d_heredoc(t_data *data, t_input_var *info, int i)
{
	char	*temp;

	temp = ft_strjoin(info->terminal_input, info->list_eof[i]);
	if (info->terminal_input != NULL)
		free(data->input_info->terminal_input);
	data->input_info->terminal_input = temp;
	info->real_eof[i] = false;
	ft_putstr_fd("warning: here-document delimited by end-of-file", 2);
	ft_putstr_fd(" (wanted '", 2);
	ft_putstr_fd(info->list_eof[i], 2);
	ft_putstr_fd("')\n", 2);
	return (SUCCESS);
}
