/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/07/07 08:49:09 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_2(t_data *data, t_input_var *info)
{
	if (refresh_mysignal_var(data) == MALLOC_ERROR)
		return (exit_codes(EXIT_1, data));
	add_history(data->input_info->first_line_and_final_text);
	info->first_line_split = ft_minishell_split(info->first_line_ref, ' ');
	if (data->input_info->first_line_split == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	ft_reformat_slash(data, data->input_info);
	//print_char_pp(info->first_line_split);
	if (check_if_we_save_variables(data, data->input_info) == true)
		save_variables(data, 0);
	if (data->fatal_error == true)
		return (MALLOC_ERROR);
	if (save_pipelines(data, data->input_info) != NO_COMMANDS)
	{
		if (data->fatal_error == true || data->write_error == true)
			return (ERROR);
		if (exec_commands(data) != SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	minishell(t_data *data)
{
	int	mini_2;

	while (data->fatal_error == false && data->exit == false)
	{
		if (recieve_complete_input(data) == SUCCESS && data->exit == false)
		{
			mini_2 = minishell_2(data, data->input_info);
			/* if (mini_2 != SUCCESS)
				return (mini_2); */
		}
		else if (data->input_info->invalid_token == true)
			add_history(data->input_info->first_line);
		data_cleanup(data);
		if (refresh_mysignal_var(data) == MALLOC_ERROR)
			return (exit_codes(EXIT_1, data));
	}
	rl_clear_history();
	total_cleanup(data);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void) argv;
	if (argc != 1)
		return (EXIT_1);
	data = data_init(env);
	if (data == NULL)
		return (EXIT_1);
	if (signal_handle() == FAILURE)
		return (exit_codes_main(EXIT_1, data));
	if (terminal_entry(data, env) == MALLOC_ERROR)
		return (exit_codes_main(EXIT_1, data));
	if (create_preset_vars(data) == MALLOC_ERROR)
		return (exit_codes_main(EXIT_1, data));
	if (minishell(data) != SUCCESS)
		return (exit_codes_main(EXIT_1, data));
	return (SUCCESS);
}
