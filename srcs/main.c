/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/18 12:53:16 by paxoc01          ###   ########.fr       */
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

void	ft_free_char_star_star(char **list)
{
	int	i;

	i = 0;
	if (list != NULL)
	{
		while (list[i] != 0)
		{
			if (list[i] != NULL)
				free(list[i]);
			i++;
		}
		free(list);
	}
}

void	ft_free_input_info(t_data *data)
{
	if (data->input_info != NULL)
	{
		if (data->input_info->final_text != NULL)
			free(data->input_info->final_text);
		if (data->input_info->first_line != NULL)
			free(data->input_info->first_line);
		if (data->input_info->first_line_and_final_text != NULL)
			free(data->input_info->first_line_and_final_text);
		if (data->input_info->first_line_ref != NULL)
			free(data->input_info->first_line_ref);
		if (data->input_info->first_line_split != NULL)
			free(data->input_info->first_line_split);
		if (data->input_info->init_input != NULL)
			free(data->input_info->init_input);
		if (data->input_info->init_input_split != NULL)
			free(data->input_info->init_input_split);
		ft_free_char_star_star(data->input_info->list_eof);
		if (data->input_info->terminal_input != NULL)
			free(data->input_info->terminal_input);
		free(data->input_info);
	}
	data->input_info = NULL;
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
			/* if (check_if_we_save_variables(data) == true)
				save_variables(data); // TO DO edit '\\' & cut string */
			if (data->malloc_error == true)
				return (MALLOC_ERROR);
			//open files (maybe after commands)
			if (save_commands(data) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			//find_command(command, env);
			//execute_commands(data); //TO DO LATER
			//delete_commands(data);
		}
		else if (data->input_info->invalid_token = true)
			add_history(data->input_info->first_line);
		ft_free_input_info(data);// TO DO free stuff
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
