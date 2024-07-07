/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/07/07 09:56:42 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_if_builtin(t_data *data, char *com)
{
	if (ft_strncmp(com, "cd", ft_strlen(com)) == 0
		|| ft_strncmp(com, "export", ft_strlen(com)) == 0
		|| ft_strncmp(com, "unset", ft_strlen(com)) == 0
		|| ft_strncmp(com, "env", ft_strlen(com)) == 0
		|| ft_strncmp(com, "exit", ft_strlen(com)) == 0)
	{
		refresh_content_com(data->command_list, data, 1);
		return (true);
	}
	return (false);
}

int	find_command(t_data *data, t_command *full_com, char **env)
{
	char	*com;

	if (check_if_builtin(data, full_com->content[0]) == false)
		return (INVALID_COMMAND);
	com = full_com->content[0];
	if (ft_command_args_errors(data->command_list->content, data) == true)
		return (ERROR);
	if (ft_strncmp(com, "cd", ft_strlen(com)) == 0)
		return (change_dir(data, full_com));
	if (ft_strncmp(com, "export", ft_strlen(com)) == 0)
	{
		if (full_com->content[1] == NULL)
			return (print_export(data));
		else
			return (export(data, full_com, &data->var, 1));
	}
	if (ft_strncmp(com, "unset", ft_strlen(com)) == 0)
		return (unset_var(data, full_com));
	if (ft_strncmp(com, "env", ft_strlen(com)) == 0)
		return (print_env(data));
	if (ft_strncmp(com, "exit", ft_strlen(com)) == 0)
	{
		data->exit = true;
		return (exit_codes(EXIT_0, data));
	}
	return (INVALID_COMMAND);
}

int	save_pipelines(t_data *data, t_input_var *info)
{
	if (data->input_info->first_line_split == NULL)
		return (0);
	while (data->input_info->first_line_split[data->idx_com] != NULL)
	{
		if (ft_there_is_equal(info->first_line_split[data->idx_com]) == true
			&& ft_isspecial(info->first_line_split[data->idx_com]) == false
			&& ft_starts_with_number(info->first_line_split[data->idx_com])
			== false)
			data->idx_com++;
		else
		{
			while (data->input_info->first_line_split[data->idx_com] != NULL)
			{
				if (write_in_command(data, data->input_info) == NO_COMMANDS)
					return (NO_COMMANDS);
				if (data->fatal_error == true)
					return (ERROR);
				if (data->input_info->first_line_split[data->idx_com] != NULL)
					data->idx_com++;
			}
		}
	}
	return (SUCCESS);
}

void	print_commands(t_data *data)
{
	t_command	*com;

	com = data->command_list;
	while (com != NULL)
	{
		if (com->content != NULL)
			print_char_pp(com->content);
		ft_printf("full path: %s\n", com->full_path);
		ft_printf("text input: %s\n", com->text_input);
		ft_printf("red input: %s\n", com->redirect_input);
		ft_printf("red output: %s\n", com->redirect_output);
		ft_printf("fd in: %i\n", com->fd_in);
		ft_printf("fd out: %i\n", com->fd_out);
		ft_printf("temp file: %s\n", com->temp_file);
		com = com->next;
	}
}
