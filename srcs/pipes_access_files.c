/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_access_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:31:23 by farah             #+#    #+#             */
/*   Updated: 2024/09/21 14:30:41 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_file_exists(char *file)
{
	if (access(file, F_OK) == -1)
		return (ERROR);
	return (SUCCESS);
}

int	ft_read_permission(char *file)
{
	if (access(file, R_OK) == -1)
		return (ERROR);
	return (SUCCESS);
}

int	ft_write_permission(char *file)
{
	if (access(file, W_OK) == -1)
		return (ERROR);
	return (SUCCESS);
}

int	ft_infile_perm(char *file, t_command *commands, t_data *data)
{
	if (ft_file_exists(file) == ERROR)
	{
		perror(file);
		exit_codes(EXIT_1, data);
		commands->no_infile = true;
		commands->temp_file = ft_strdup(file);
		if (commands->temp_file == NULL)
			return (error_i(MALLOC_ERROR, data));
		if (ft_open_infile(file, commands) == ERROR)
			return (error_i(OPEN_ERROR, data));
	}
	else if (ft_read_permission(file) == ERROR)
	{
		perror(file);
		exit_codes(EXIT_1, data);
		commands->no_permissions = true;
		commands->temp_file = ft_create_file_name(data);
		if (commands->temp_file == NULL)
			return (error_i(MALLOC_ERROR, data));
		if (ft_open_infile(commands->temp_file, commands) == ERROR)
			return (error_i(OPEN_ERROR, data));
	}
	else if (ft_open_infile(file, commands) == ERROR)
		return (error_i(OPEN_ERROR, data));
	return (SUCCESS);
}

int	ft_outfile_perm(char *file, t_command *commands, t_data *data)
{
	if (ft_file_exists(file) == ERROR)
	{
		if (ft_open_outfile(file, commands) == ERROR)
			return (error_i(OPEN_ERROR, data));
		return (SUCCESS);
	}
	if (ft_write_permission(file) == ERROR)
	{
		perror(file);
		return (error_i(WRITE_ERROR, data));
	}
	if (ft_open_outfile(file, commands) == ERROR)
		return (error_i(OPEN_ERROR, data));
	return (SUCCESS);
}
