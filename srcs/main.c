/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/20 17:36:48 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_mysignal = 0;

char	*ft_user_text(char *eof, t_data *data)
{
	char	*input;
	char	*user_text;

	user_text = NULL;
	while (42)
	{
		input = readline("> ");
		if (ft_samestr(input, eof) == true)
			return (user_text);
		user_text = ft_strjoin(user_text, input);
	}
}

int	minishell(char **env)
{
	t_data	*data;

	data = data_init();
	if (data == NULL)
		return (MALLOC_ERROR);
	terminal_entry(data, env);
	while (g_mysignal == 0 && data->malloc_error == false
		&& data->exit == false) //find more reasons to break
	{
		//data->input = readline(data->entry);
		if (recieve_complete_input(data) == SUCCESS)
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
			if (save_pipelines(data) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			if (ft_file_permissions(data->command_list) == ERROR)
				return (ERROR);
			print_commands(data);
			//pipe_exec_coms(data);
			//find_command(command, env);
			//execute_commands(data); //TO DO LATER
			//delete_commands(data);
		}
		else if (data->input_info->invalid_token == true)
			add_history(data->input_info->first_line);
		data_cleanup(data);// TO DO free stuff
	}
	// TO DO free even more stuff
	rl_clear_history();
	return (EXIT_SUCCESS);
}

//what happens when export? do we save_variables or execute_commands

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void) argc;
	(void) argv;
	if (minishell(env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
}
