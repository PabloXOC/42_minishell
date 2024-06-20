/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:33:59 by paxoc01           #+#    #+#             */
/*   Updated: 2024/06/20 15:50:27 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	ft_open_out(char *file, t_data *data, bool trunc)
{
	if (data->fd_out > 0)
	{
		if (close(data->fd_out) == -1)
			return (ft_write_error_i(CLOSE_ERROR, data));
	}
	if (trunc == true)
		data->fd_out = open(file, O_TRUNC);
	else
		data->fd_out = open(file, O_RDWR);
	if (write(data->fd_out, "", 0) == -1)
		return (ft_write_error_i(WRITE_ERROR, data));
	return (SUCCESS);
} */
