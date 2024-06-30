/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/29 00:16:07 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char	*ft_user_text(char *eof, t_data *data)
{
	char	*input;
	char	*user_text;

	user_text = NULL;
	while (42)
	{
		input = readline("> ");
		if (input == NULL)
			printf("AA%sAA\n", input);
		if (ft_samestr(input, eof) == true)
			return (user_text);
		user_text = ft_strjoin(user_text, input);
	}
} */



int	minishell(t_data *data)
{
	while (g_exit_status == 0 && data->malloc_error == false
		&& data->exit == false) //find more reasons to break
	{
		//data->input = readline(data->entry);
		if (g_exit_status == 0 && recieve_complete_input(data) == SUCCESS )
		{
			add_history(data->input_info->first_line_and_final_text);
			//data->input = ft_reformat_input(data->input, data); // reformat and split input (not \\)
			data->input_info->first_line_split = ft_minishell_split(data->input_info->first_line_ref, ' ');
			if (data->input_info->first_line_split == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
			if (data->malloc_error == true)
				return (MALLOC_ERROR);
			if (check_if_we_save_variables(data) == true) //check for "" and '' (special characters allowed in "" '')
				save_variables(data); // TO DO edit '\\' & cut string
			if (data->malloc_error == true)
				return (MALLOC_ERROR);
			if (save_pipelines(data) != NO_COMMANDS)
				if (exec_commands(data) != SUCCESS)
					return (FAILURE);
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

	(void)argc;
	(void)argv;
	if (argc != 1)
		return (ERROR);
	data = data_init(env);
	if (data == NULL)
		return (MALLOC_ERROR);
	signal_handle();
	terminal_entry(data, env);
	refresh_mysignal_var(data);
	if (minishell(data) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
