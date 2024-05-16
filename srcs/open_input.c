/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:43:17 by paxoc01           #+#    #+#             */
/*   Updated: 2024/05/15 17:08:16 by paxoc01          ###   ########.fr       */
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

static int ft_readsize(char	*str, char *eof)
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

static int	ft_open(char *file, t_data *data)
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

static int	ft_read(char *eof, t_data *data)
{
	int		size;

	size = ft_readsize(data->next_eof, eof);
	data->text_input = (char *) malloc ((size + 1) * sizeof(char));
	if (data->text_input == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	ft_memcpy(data->text_input, data->next_eof, size);
	data->text_input[size] = 0;
	data->next_eof = &data->next_eof[size + ft_strlen(eof) + 2];
	return (SUCCESS);
}

int	open_input(t_data *data)
{
	int	i;

	i = 0;
	while (data->input_split[i] != 0 && ft_samestr(data->input_split[i], "\n") == false)
	{
		printf("LINE %d: %s\n", i, (data->input_split[i]));
		if (ft_samestr(data->input_split[i], "<") == true)
		{
			write(1, "yo\n", 3);
			i++;
			if (data->text_input != NULL)
				free(data->text_input);
			if (ft_open(data->input_split[i], data) != SUCCESS)
				return (FAILURE);
		}
		if (ft_samestr(data->input_split[i], "<<") == true)
		{
			write(1, "by\n", 3);
			i++;
			if (data->text_input != NULL)
				free(data->text_input);
			if (ft_read(data->input_split[i], data) != SUCCESS)
				return (FAILURE);
		}
		i++;
	}
}
