/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/05/04 14:38:28 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_mysignal;

g_mysignal = 0;

/* int	check_errors(command)
{
	//look for multiple tokens in a row
	//check if commands exist && find if correct arguments/flags
	//finding the path of the command
} */

char	*ft_join_path_command(char *command, char **paths, int i)
{
	char	*str;
	char	*str2;

	str = ft_strjoin(paths[i], "/");
	if (!(str))
		return (ft_write_error_c(MALLOC_ERROR, command));
	str2 = ft_strjoin(str, command);
	free(str);
	if (!(str2))
		return (ft_write_error_c(MALLOC_ERROR, command));
	return (str2);
}

char	*ft_full_command(t_data *data, char **paths)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i] != 0)
	{
		full_path = ft_join_path_command(data->input_split[0], paths, i);
		if (full_path == NULL)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

/* int	ft_parse_input(t_data *data, char **env)
{
	char		**paths;
	int			i;

	i = 0;
	data->input_split = ft_split(data->input, ' ');
	if (data->input_split == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	if (ft_correct_input(data->input_split[0]) == FAILURE)
		return (FAILURE);
	while (env[i] != 0)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(ft_strchr(env[i], '/'), ':');
			if (paths == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
			break ;
		}
		i++;
	}
	data->full_address = ft_full_command(data, paths);
	printf("Command: %s\n", data->full_address);
	return (SUCCESS);
} */

int	recieve_complete_input(t_data *data)
{
	char	*more_input;
	char	*joined_input;
	char	*temp_input;

	if (ft_empty(data->input) == true)
		return (EMPTY);
	while (ft_not_complete(data->input, data) == true)
	{
		data->input = ft_join_input(data->input, "\n");
		if (data->input == NULL)
			return (ft_write_error_c(MALLOC_ERROR, data));
		more_input = readline("> ");
		data->input = ft_strjoin(data->input, more_input);
		free(more_input);
	}
	return (SUCCESS);
}

int	minishell(char **env)
{
	t_data	*data;

	data = data_init();
	if (data == NULL)
		return (MALLOC_ERROR);
	terminal_entry(data, env);
	while (g_mysignal == 0 && data->malloc_error == false
		&& data->exit = false) //find more reasons to break
	{
		data->input = readline(data->entry);
		if (recieve_complete_input(data) == SUCCESS)
		{
			//TO DO if << command->user_text = recieve_input();
			add_history(data->input);  //TO DO  merge in different variable input + user text (if <<)
			data->input = ft_reformat_input(data->input, data);
			if (data->malloc_error == true)
				return (MALLOC_ERROR);
			if (check_if_we_save_variables(data) == true) //TO DO check =, non-alpha-num, pipes
				save_variables(data); // TO DO save variables & edit '\\' & cut string
			if (data->malloc_error == true)
				return (MALLOC_ERROR);
			if (save_commands(data) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			//find_command(command, env);
			if (check_errors(data) == true)  //TO DO
				return (FAILURE);  //specify errors
			execute_commands(data); //TO DO LATER
			delete_commands(data);
		}
		// TO DO free stuff
	}
	// TO DO free even more stuff
	rl_clear_history();
	return (EXIT_SUCCESS);
}


int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	if (minishell(env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
