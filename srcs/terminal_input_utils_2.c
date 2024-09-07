/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_input_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:41:15 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/04 19:17:05 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_control_d_heredoc(t_data *data, t_input_var *info_g, int i)
{
	char	*temp;

	temp = ft_strjoin(info_g->terminal_input, info_g->list_eof[i]);
	if (info_g->terminal_input != NULL)
		free(info_g->terminal_input);
	info_g->terminal_input = temp;
	info_g->real_eof[i] = false;
	ft_putstr_fd("warning: here-document delimited by end-of-file", 2);
	ft_putstr_fd(" (wanted '", 2);
	ft_putstr_fd(info_g->list_eof[i], 2);
	ft_putstr_fd("')\n", 2);
	return (SUCCESS);
}
