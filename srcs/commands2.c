/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/11/12 13:32:17 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_command2(t_data *data, t_command *full_com, char *com)
{
	if (ft_strncmp(com, "unset", ft_strlen(com) + 1) == 0)
		return (unset_var(data, full_com));
	if (ft_strncmp(com, "env", ft_strlen(com) + 1) == 0)
		return (print_env(data));
	if (ft_strncmp(com, "exit", ft_strlen(com) + 1) == 0)
		return (handle_exit(full_com, data));
	return (INVALID_COMMAND);
}

int	find_command(t_data *data, t_command *full_com)
{
	char	*com;

	com = full_com->content[0];
	if (full_com->previous_error == true)
	{
		exit_codes(EXIT_2, NULL);
		return (SUCCESS);
	}
	if (ft_command_args_errors(data->spec[data->sc_n]
			->command_list->content, data) == true)
		return (ERROR);
	if (ft_strncmp(com, "echo", ft_strlen(com) + 1) == 0)
		return (exec_echo(full_com, 1, false));
	if (ft_strncmp(com, "cd", ft_strlen(com) + 1) == 0)
		return (change_dir(data, full_com));
	if (ft_strncmp(com, "export", ft_strlen(com) + 1) == 0)
	{
		if (full_com->content[1] == NULL)
			return (print_export(data));
		else
			return (export(data, full_com, &data->var, 1));
	}
	return (find_command2(data, full_com, com));
}

int	save_pipelines(t_data *data, t_info *info, t_spec *spec)
{
	if (info->first_line_split == NULL)
		return (0);
	while (info->first_line_split[data->v->idx_com] != NULL)
	{
		if (ft_there_is_equal(info->first_line_split[data->v->idx_com]) == true
			&& ft_isspecial(info->first_line_split[data->v->idx_com]) == false
			&& ft_starts_with_number(info->first_line_split[data->v->idx_com])
			== false)
			data->v->idx_com++;
		else
		{
			while (info->first_line_split[data->v->idx_com] != NULL)
			{
				if (write_in_command(data, spec, info, 0) == AMBIG_REDIRECT)
					return (AMBIG_REDIRECT);
				if (data->fatal_error == true)
					return (ERROR);
				if (info->first_line_split[data->v->idx_com] != NULL)
					data->v->idx_com++;
			}
		}
	}
	if (spec->no_commands == true)
		return (NO_COMMANDS);
	return (SUCCESS);
}

void	print_commands(t_data *data)
{
	t_command	*com;

	com = data->spec[data->sc_n]->command_list;
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
