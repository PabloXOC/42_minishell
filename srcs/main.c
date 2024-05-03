/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/05/03 17:28:22 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_mysignal;

int	ft_correct_input(char *input)
{
	//remove the beginning and end of the input (spaces) TO DO
	if (ft_samestr(input, "cd") == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (ft_samestr(input, "echo") == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (ft_samestr(input, "pwd") == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (ft_samestr(input, "export") == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (ft_samestr(input, "unset") == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (ft_samestr(input, "env") == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (ft_samestr(input, "exit") == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

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

int	ft_parse_input(t_data *data, char **env)
{
	char		**paths;
	int			i;

	i = 0;
	data->split_input = ft_split(data->input, ' ');
	if (data->split_imput == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	data->n_words = ft_count_words(data->input_split);
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
}

int	ft_first_check(t_data *data)
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
	long		i;
	t_data	*data;

	data = command_init();
	if (data == NULL)
		return (MALLOC_ERROR);
	terminal_entry(data, env);
	while (g_mysignal == 0)
	{
		data->input = readline(data->entry);
		if (ft_first_check(data) == SUCCESS)
		{
			if (ft_parse_input(data, env) == EXIT_FAILURE)
				ft_printf("Command '%s' not found.\n", data->input_split[0]);
			save_commands(data);
			safe_var(data);
			//find_command(command, env);
			add_history(data->input);
			delete_commands(data);
		}
		//parse input TO DO
		//find command TO DO
		if (data->exit == 1)
			g_mysignal = 1;
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}


int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	//printf("%s\n", ft_reformat_input("hola \\\\\\\\que tal\\\\\\ me llamo \\pablo\\\\"));
	if (minishell(env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
