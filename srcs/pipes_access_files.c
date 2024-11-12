/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_access_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:31:23 by farah             #+#    #+#             */
/*   Updated: 2024/11/11 15:00:06 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_write_permission(char *file)
{
	if (access(file, W_OK) == -1)
		return (ERROR);
	return (SUCCESS);
}

int	ft_infile_perm2(t_data *data, t_command *commands, char *file)
{
	perror(file);
	exit_codes(EXIT_1, data);
	commands->previous_error = true;
	commands->no_permissions = true;
	commands->temp_file = ft_create_file_name(data);
	if (commands->temp_file == NULL)
		return (error_i(MALLOC_ERROR, data));
	ft_open_infile(commands->temp_file, commands, data);
	return (SUCCESS);
}

int	ft_infile_perm(char *file, t_command *commands, t_data *data, int ret)
{
	if (ft_file_exists(file) == ERROR)
	{
		perror(file);
		exit_codes(EXIT_1, data);
		commands->previous_error = true;
		commands->no_infile = true;
		commands->temp_file = ft_strdup(file);
		if (commands->temp_file == NULL)
			return (error_i(MALLOC_ERROR, data));
		ft_open_infile(file, commands, data);
	}
	else if (ft_read_permission(file) == ERROR)
	{
		ret = ft_infile_perm2(data, commands, file);
		if (ret != SUCCESS)
			return (ret);
	}
	else
		ft_open_infile(file, commands, data);
	return (SUCCESS);
}

int	ft_outfile_perm(char *file, t_command *commands, t_data *data)
{
	if (ft_file_exists(file) == ERROR)
	{
		ft_open_outfile(file, commands, data);
		return (SUCCESS);
	}
	if (ft_write_permission(file) == ERROR)
	{
		perror(file);
		commands->previous_error = true;
		return (error_i(WRITE_ERROR, data));
	}
	ft_open_outfile(file, commands, data);
	return (SUCCESS);
}
