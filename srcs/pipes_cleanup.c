/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/11/12 13:52:12 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_infiles_cleanup_extra(t_command *commands)
{
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

void	ft_infiles_cleanup(t_command *commands)
{
	if (commands->fd_in > 2)
		close(commands->fd_in);
	if (commands->no_infile == true)
	{
		unlink(commands->redirect_input);
		commands->no_infile = false;
		if (commands->temp_file != NULL)
		{
			free(commands->temp_file);
			commands->temp_file = NULL;
		}
	}
	ft_infiles_cleanup_extra(commands);
}

void	ft_outfiles_cleanup(t_command *commands)
{
	if (commands->fd_out > 2)
		close(commands->fd_out);
	if (commands->err_open_out_file == true)
	{
		if (commands->out_temp_file != NULL)
		{
			unlink(commands->out_temp_file);
			free(commands->out_temp_file);
			commands->out_temp_file = NULL;
		}
		commands->err_open_out_file = false;
	}
}
