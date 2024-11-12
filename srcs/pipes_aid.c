/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_aid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/09/28 16:52:02 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_char_pp_len(char **stack)
{
	int	i;

	i = 0;
	while (stack[i] != NULL)
		i++;
	return (i);
}

int	ft_open_infile(char *file, t_command *commands, t_data *data)
{
	int		fd;

	fd = open(file, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		commands->no_infile = true;
		if (commands->temp_file != NULL)
			free(commands->temp_file);
		if (commands->redirect_input != NULL)
			free(commands->redirect_input);
		commands->temp_file = ft_create_file_name(data);
		if (commands->temp_file == NULL)
			return (error_i(MALLOC_ERROR, data));
		commands->redirect_input = ft_strdup(commands->temp_file);
		if (commands->redirect_input == NULL)
			return (error_i(MALLOC_ERROR, data));
		fd = open(commands->temp_file, O_RDONLY | O_CREAT, 0644);
	}
	commands->fd_in = fd;
	return (SUCCESS);
}

int	ft_open_outfile(char *file, t_command *commands, t_data *data)
{
	int		fd;

	if (commands->append_output == false)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(file);
		commands->err_open_out_file = true;
		if (commands->out_temp_file != NULL)
			free(commands->out_temp_file);
		commands->out_temp_file = ft_create_file_name(data);
		if (commands->out_temp_file == NULL)
			return (error_i(MALLOC_ERROR, data));
		fd = open(commands->out_temp_file, O_RDWR | O_CREAT, 0644);
	}
	commands->fd_out = fd;
	return (SUCCESS);
}

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
