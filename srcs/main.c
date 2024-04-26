/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/26 13:23:27 by paxoc01          ###   ########.fr       */
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

char	*ft_full_command(t_command *command, char **paths)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i] != 0)
	{
		full_path = ft_join_path_command(command->command_parsed[0], paths, i);
		if (full_path == NULL)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	ft_parse_input(t_command *command, char **env)
{
	char		**paths;
	int			i;

	i = 0;
	command->command_parsed = ft_split(command->input, ' ');
	if (command->command_parsed == NULL)
		return (ft_write_error_i(MALLOC_ERROR, command));
	command->n_words = ft_count_words(command->command_parsed);
	if (ft_correct_input(command->command_parsed[0]) == FAILURE)
		return (FAILURE);
	while (env[i] != 0)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(ft_strchr(env[i], '/'), ':');
			if (paths == NULL)
				return (ft_write_error_i(MALLOC_ERROR, command));
			break ;
		}
		i++;
	}
	command->full_address = ft_full_command(command, paths);
	printf("Command: %s\n", command->full_address);
	return (SUCCESS);
}

int	ft_first_check(t_command *command)
{
	char	*more_input;
	char	*joined_input;
	char	*temp_input;

	if (ft_empty(command->input) == true)
		return (EMPTY);
	while (ft_not_complete(command->input, command) == true)
	{
		command->input = ft_join_input(command->input, "\n");
		if (command->input == NULL)
			return (ft_write_error_c(MALLOC_ERROR, command));
		more_input = readline("> ");
		command->input = ft_strjoin(command->input, more_input);
		free(more_input);
	}
	return (SUCCESS);
}

int	minishell(char **env)
{
	long		i;
	t_command	*command;

	while (g_mysignal == 0)
	{
		command = command_init();
		if (command == NULL)
			return (MALLOC_ERROR);
		command->input = readline("pabloXOC$ ");
		if (ft_first_check(command) == SUCCESS)
		{
			if (ft_parse_input(command, env) == EXIT_FAILURE)
				ft_printf("Command '%s' not found.\n", command->command_parsed[0]);
			find_command(command, env);
			add_history(command->input);
		}
		//parse input TO DO
		//find command TO DO
		if (command->exit == 1)
			g_mysignal = 1;
	}
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
