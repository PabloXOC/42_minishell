/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/11/05 17:19:54 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_full_n(char *str)
{
	int i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] != 0)
	{
		if (ft_isdigit(str[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

int	ft_atoi_exit(const char *str)
{
	int	loop;
	int	temp;

	temp = 0;
	loop = 0;
	while (str[loop] == 32)
		loop++;
	if (str[loop] == '+' || str[loop] == '-')
		loop++;
	while (str[loop] >= '0' && str[loop] <= '9')
	{
		temp = 10 * temp + str[loop] - '0';
		loop++;
	}
	return (temp);
}

int	count_arg(char **args)
{
	int	i;

	i = 0;
	while (args[i] != 0)
		i++;
	return (i);
}

int	handle_exit(t_command *full_com, t_data *data)
{
	data->exit = true;
	write(1, "exit\n", 5);
	if (count_arg(full_com->content) == 1)
		exit_codes(EXIT_0, data);
	else if (count_arg(full_com->content) > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		exit_codes(EXIT_1, data);
	}
	else if (is_full_n(full_com->content[1]) == false)
	{
		write(2, "exit: numeric argument required\n", 32);
		return (exit_codes(EXIT_1, data));
	}
	else
		exit_codes(ft_atoi_exit(full_com->content[1]), data);
	return (SUCCESS);
}

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
