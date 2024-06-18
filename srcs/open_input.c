/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:43:17 by paxoc01           #+#    #+#             */
/*   Updated: 2024/06/18 16:33:44 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_filesize(char *file, t_data *data)
{
	int		size;
	int		fd;
	char	buffer[1];

	size = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_write_error_i(OPEN_ERROR, data));
	if (read(fd, buffer, 0) == -1)
		return (ft_write_error_i(READ_ERROR, data));
	while (read(fd, buffer, 1) == 1)
		size++;
	if (close(fd) == -1)
		return (ft_write_error_i(CLOSE_ERROR, data));
	return (size);
}

static int	ft_readsize(char	*str, char *eof)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\n')
		{
			if (ft_memcmp(&str[i + 1], eof, ft_strlen(eof)) == 0
				&& str[i + 1 + ft_strlen(eof)] == '\n')
			{
				return (i);
			}
		}
		i++;
	}
}

static int	ft_open_in(char *file, t_data *data)
{
	int		fd;
	int		filesize;
	char	*buffer;

	filesize = ft_filesize(file, data);
	if (filesize == -1)
		return (FAILURE);
	fd = open(file, O_RDONLY);
	buffer = (char *) malloc ((filesize + 1) * sizeof(char));
	if (buffer == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	if (read(fd, NULL, 0) == -1)
		return (ft_write_error_i(READ_ERROR, data));
	read(fd, buffer, filesize);
	buffer[filesize] = 0;
	data->text_input = buffer;
	if (close(fd) == -1)
		return (ft_write_error_i(CLOSE_ERROR, data));
	return (SUCCESS);
}

static int	ft_read(t_data *data)
{
	int		size;

	data->text_input = ft_strdup(data->input_info->final_text_last);
	if (data->text_input == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	return (SUCCESS);
}

int	open_input(t_data *data)
{
	int	i;

	i = 0;
	while (data->input_info->first_line_split[i] != 0
		&& ft_samestr(data->input_info->first_line_split[i], "\n") == false)
	{
		if (ft_samestr(data->input_info->first_line_split[i], "<") == true)
		{
			i++;
			if (data->text_input != NULL)
				free(data->text_input);
			if (ft_open_in(data->input_info->first_line_split[i], data) != SUCCESS)
				return (FAILURE);
		}
		if (ft_samestr(data->input_info->first_line_split[i], "<<") == true)
		{
			i++;
			if (data->text_input != NULL)
				free(data->text_input);
			if (ft_read(data) != SUCCESS)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
