/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:27:40 by ffauth-p          #+#    #+#             */
/*   Updated: 2024/11/05 15:04:53 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_input_info2(t_data *data, t_info *info, t_command *com, int i)
{
	if (identify_amb(info->first_line_split[i + 1], data) == AMBIG_REDIRECT)
		return (AMBIG_REDIRECT);
	ft_infiles_cleanup(com);
	ft_assemble_file_name(data, &info->first_line_split[i + 1]);
	com->redirect_input = ft_strdup(info->first_line_split[i + 1]);
	if (com->redirect_input == NULL)
		return (error_i(MALLOC_ERROR, data));
	com->file_input = true;
	if (com->redirect_input != NULL)
		if (ft_infile_perm(com->redirect_input, com, data, 0) != SUCCESS)
			return (READ_ERROR);
	return (SUCCESS);
}

int	fill_input_info(t_data *data, t_info *info, int i, t_command *com)
{
	if (ft_strncmp(info->first_line_split[i], "<<", 2) == 0)
	{
		if (identify_amb(info->first_line_split[data->v->pointer + 1],
				data) == AMBIG_REDIRECT)
			return (AMBIG_REDIRECT);
		ft_infiles_cleanup(com);
		com->text_input = ft_strdup(info->text_input[data->v->pointer++]);
		if (com->text_input == NULL)
			return (error_i(MALLOC_ERROR, data));
		com->file_input = false;
		if (com->file_input == false && com->text_input != NULL)
		{
			if (create_temp_file(com, data) != SUCCESS)
				return (MALLOC_ERROR);
			if (ft_infile_perm(com->temp_file, com, data, 0) != SUCCESS)
				return (READ_ERROR);
		}
		return (SUCCESS);
	}
	else if (ft_strncmp(info->first_line_split[i], "<", 1) == 0)
	{
		return (fill_input_info2(data, info, com, i));
	}
	return (ERROR);
}

int	fill_output_info2(t_data *data, t_info *info, t_command *com, int i)
{
	if (identify_amb(info->first_line_split[i + 1], data) == AMBIG_REDIRECT)
		return (AMBIG_REDIRECT);
	ft_assemble_file_name(data, &info->first_line_split[i + 1]);
	com->redirect_output = ft_strdup(info->first_line_split[i + 1]);
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

int	fill_output_info(t_data *data, t_info *info, int i, t_command *com)
{
	if (ft_strncmp(info->first_line_split[i], ">>", 2) == 0)
	{
		if (identify_amb(info->first_line_split[i + 1], data) == AMBIG_REDIRECT)
			return (AMBIG_REDIRECT);
		ft_assemble_file_name(data, &info->first_line_split[i + 1]);
		com->redirect_output = ft_strdup(info->first_line_split[i + 1]);
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
		return (fill_output_info2(data, info, com, i));
	}
	return (ERROR);
}

int	fill_extra_info(t_data *data, t_info *info, int i, t_command *com)
{
	int	ret;

	ret = fill_input_info(data, info, i, com);
	if (ret == AMBIG_REDIRECT)
		return (AMBIG_REDIRECT);
	if (ret != ERROR)
		return (SUCCESS);
	ret = fill_output_info(data, info, i, com);
	if (ret == AMBIG_REDIRECT)
		return (AMBIG_REDIRECT);
	if (ret != ERROR)
		return (SUCCESS);
	return (ERROR);
}
