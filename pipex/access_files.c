/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:31:23 by farah             #+#    #+#             */
/*   Updated: 2024/02/23 19:52:04 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include "pipex.h"

int	ft_file_exists(char *file)
{
	if (access(file, F_OK) == -1)
		return (ERROR);
	return (OK);
}

int	ft_read_permission(char *file)
{
	if (access(file, R_OK) == -1)
		return (ERROR);
	return (OK);
}

int	ft_write_permission(char *file)
{
	if (access(file, W_OK) == -1)
		return (ERROR);
	return (OK);
}

int	ft_infile_permissions(char *file, t_info *commands)
{
	if (ft_file_exists(file) == ERROR)
	{
		perror(file);
		commands->no_infile = 1;
		if (ft_open_infile(file, commands) == ERROR)
			return (ERROR);
		return (NO_INFILE);
	}
	if (ft_read_permission(file) == ERROR)
	{
		perror(file);
		commands->no_permissions = 1;
		commands->temp_file = ft_create_file_name();
		if (ft_open_infile(commands->temp_file, commands) == ERROR)
			return (ERROR);
		return (NO_PERMISSIONS);
	}
	if (ft_open_infile(file, commands) == ERROR)
		return (ERROR);
	return (OK);
}

int	ft_outfile_permissions(char *file, t_info *commands)
{
	if (ft_file_exists(file) == ERROR)
	{
		if (ft_open_outfile(file, commands) == ERROR)
			return (ERROR);
		return (OK);
	}
	if (ft_write_permission(file) == ERROR)
	{
		perror(file);
		return (ERROR);
	}
	if (ft_open_outfile(file, commands) == ERROR)
		return (ERROR);
	return (OK);
}
