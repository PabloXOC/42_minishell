/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/20 17:23:04 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_2(t_data *data, t_specific *spec, t_input_var *info)
{
	if (refresh_mysignal_var(data) == MALLOC_ERROR)
		return (exit_codes(EXIT_1, data));
	if (ft_empty(spec->input_info->first_line_ref) == true) //make better
		return (ft_write_error_i(EMPTY, data));
	ft_reformat_vars(data, info);
	info->first_line_split = ft_minishell_split(info->first_line_vars, ' ');
	if (info->first_line_split == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	if (check_if_we_save_variables(data, info) == true)
		save_variables(data, info, 0);
	if (data->fatal_error == true)
		return (MALLOC_ERROR);
	if (save_pipelines(data, info, spec) != NO_COMMANDS)
	{
		if (reformat_final(data, spec) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		//print_char_pp(info->spec->command_list->content);
		if (data->fatal_error == true || data->v->write_error == true)
			return (ERROR);
		if (exec_commands(data) != SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	minishell1(t_data *data)
{
	int	mini_2;
	int	ret;

	ft_reset_vars(data);
	ret = recieve_complete_input(data);
	if (ret == SUCCESS && data->exit == false)
	{
		add_history(data->input_info_g->first_line_and_final_text);
		data->sc_pos = 0;
		while (data->sc_pos <= data->n_semicolons)
		{
			ft_reset_vars(data);
			mini_2 = minishell_2(data, data->specific[data->sc_pos],
				data->specific[data->sc_pos]->input_info);
			if (mini_2 == MALLOC_ERROR)
				return (MALLOC_ERROR);
			data->sc_pos++;
		}
	}
	else if (ret == MALLOC_ERROR)
		return (MALLOC_ERROR);
	else if (data->input_info_g->invalid_token == true
		|| data->input_info_g->incomplete_input == true)
		add_history(data->input_info_g->first_line);
	return (SUCCESS);
}

int	minishell(t_data *data)
{
	while (data->fatal_error == false && data->exit == false)
	{
		if (minishell1(data) == MALLOC_ERROR)
		{
			total_cleanup(data);
			return (MALLOC_ERROR);
		}
		if (data->exit == false)
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
	if (terminal_entry_info(data, env) == MALLOC_ERROR)
		return (exit_codes_main(EXIT_1, data));
	if (create_preset_vars(data) == MALLOC_ERROR)
		return (exit_codes_main(EXIT_1, data));
	if (minishell(data) != SUCCESS)
		return (exit_codes_main(EXIT_1, data));
	return (SUCCESS);
}
