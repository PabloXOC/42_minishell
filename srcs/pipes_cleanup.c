/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/07/01 13:30:50 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_infiles_cleanup(t_command *commands)
{
	if (commands->fd_in > 2)
		close(commands->fd_in);
	if (commands->no_infile == true)
	{
		unlink(commands->redirect_input);
		commands->no_infile = false;
	}
	if (commands->no_permissions == true)
	{
		if (commands->temp_file != NULL)
		{
			unlink(commands->temp_file);
			free(commands->temp_file);
			commands->temp_file = NULL;
		}
		commands->no_permissions = false;
	}
	if (commands->file_input == false && commands->temp_file != NULL)
	{
		unlink(commands->temp_file);
		free(commands->temp_file);
		commands->temp_file = NULL;
		commands->file_input = true;
	}
}
