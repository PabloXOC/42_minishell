/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:27:40 by ffauth-p          #+#    #+#             */
/*   Updated: 2024/09/21 17:20:32 by paxoc01          ###   ########.fr       */
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

int	fill_input_info(t_data *data, t_info *info, int i, t_command *com)
{
	if (ft_strncmp(info->first_line_split[i], "<<", 2) == 0)
	{
		ft_infiles_cleanup(com);
		com->text_input = ft_strdup(info->text_input[data->v->pointer++]);
		if (com->text_input == NULL)
			return (error_i(MALLOC_ERROR, data));
		com->file_input = false;
		if (com->file_input == false && com->text_input != NULL)
		{
			if (create_temp_file(com, data) != SUCCESS)
				return (MALLOC_ERROR);
			if (ft_infile_perm(com->temp_file, com, data) != SUCCESS)
				return (READ_ERROR);
		}
		return (SUCCESS);
	}
	else if (ft_strncmp(info->first_line_split[i], "<", 1) == 0)
	{
		ft_infiles_cleanup(com);
		com->redirect_input = ft_strdup(info->first_line_split[++i]);
		if (com->redirect_input == NULL)
			return (error_i(MALLOC_ERROR, data));
		com->file_input = true;
		if (com->redirect_input != NULL)
			if (ft_infile_perm(com->redirect_input, com, data) != SUCCESS)
				return (READ_ERROR);
		return (SUCCESS);
	}
	return (ERROR);
}

int	fill_output_info(t_data *data, t_info *info, int i, t_command *com)
{
	if (ft_strncmp(info->first_line_split[i], ">>", 2) == 0)
	{
		com->redirect_output = ft_strdup(info->first_line_split[++i]);
		if (com->redirect_output == NULL)
			return (error_i(MALLOC_ERROR, data));
		com->append_output = true;
		if (com->fd_out > 2)
			close(com->fd_out);
		if (com->redirect_output != NULL)
			if (ft_outfile_perm(com->redirect_output, com, data) != SUCCESS)
				return (WRITE_ERROR);
		return (SUCCESS);
	}
	else if (ft_strncmp(info->first_line_split[i], ">", 1) == 0)
	{
		com->redirect_output = ft_strdup(info->first_line_split[++i]);
		if (com->redirect_output == NULL)
			return (error_i(MALLOC_ERROR, data));
		com->append_output = false;
		if (com->fd_out > 2)
			close(com->fd_out);
		if (com->redirect_output != NULL)
			if (ft_outfile_perm(com->redirect_output, com, data) == ERROR)
				return (WRITE_ERROR);
		return (SUCCESS);
	}
	return (ERROR);
}

int	fill_extra_info(t_data *data, t_info *info, int i, t_command *com)
{
	if (fill_input_info(data, info, i, com) != ERROR)
	{
		i++;
		return (SUCCESS);
	}
	else if (fill_output_info(data, info, i, com) != ERROR)
	{
		i++;
		return (SUCCESS);
	}
	return (ERROR);
}
