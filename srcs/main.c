/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/07/02 19:47:42 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(t_data *data)
{
	while (data->fatal_error == false && data->exit == false)
	{
		if (recieve_complete_input(data) == SUCCESS && data->exit == false)
		{
			if (refresh_mysignal_var(data) == MALLOC_ERROR)
				return (exit_codes(EXIT_1, data));
			add_history(data->input_info->first_line_and_final_text);
			data->input_info->first_line_split = ft_minishell_split(data->input_info->first_line_ref, ' ');
			if (data->input_info->first_line_split == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
			// TO DO edit '\\' & cut string
			if (check_if_we_save_variables(data, data->input_info) == true)
				save_variables(data);
			if (data->fatal_error == true)
				return (MALLOC_ERROR);
			if (save_pipelines(data, data->input_info) != NO_COMMANDS)
			{
				if (data->fatal_error == true)
					return (ERROR);
				if (exec_commands(data) != SUCCESS)
					return (FAILURE);
			}
		}
		else if (data->input_info->invalid_token == true)
			add_history(data->input_info->first_line);
		data_cleanup(data);
	}
	rl_clear_history();
	total_cleanup(data);
	return (SUCCESS);
}

//what happens when export? do we save_variables or execute_commands

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
	if (refresh_mysignal_var(data) == MALLOC_ERROR)
		return (exit_codes_main(EXIT_1, data));
	if (minishell(data) != SUCCESS)
		return (exit_codes_main(EXIT_1, data));
	return (SUCCESS);
}
