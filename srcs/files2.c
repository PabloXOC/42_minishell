/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:50:13 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/28 16:51:47 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_temp_file(t_command *com, t_data *data)
{
	int	fd;

	com->temp_file = ft_create_file_name(data);
	if (com->temp_file == NULL)
		return (MALLOC_ERROR);
	fd = open(com->temp_file, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
		return (error_i(OPEN_ERROR, data));
	write(fd, com->text_input, ft_strlen(com->text_input));
	close(fd);
	return (SUCCESS);
}
