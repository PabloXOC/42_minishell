/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/25 14:13:48 by paxoc01          ###   ########.fr       */
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
		return (NULL);
	str2 = ft_strjoin(str, command);
	free(str);
	if (!(str2))
		return (NULL);
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
		{
			perror("Malloc error");
			return (NULL);
		}
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

t_command	*ft_parse_input(char *input, char **env)
{
	t_command	*command;
	char		**paths;
	int			i;

	i = 0;
	command = (t_command *) malloc (sizeof (t_command));
	command->command_parsed = ft_split(input, ' ');
	command->n_words = ft_count_words(command->command_parsed);
	if (ft_correct_input(command->command_parsed[0]) == EXIT_FAILURE)
		return (NULL);
	while (env[i] != 0)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(ft_strchr(env[i], '/'), ':');
			if (paths == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	command->full_address = ft_full_command(command, paths); //TO DO
	printf("Command: %s\n", command->full_address);
	return (command);
}

int	ft_first_check(char *input)
{
	if (ft_empty(input) == true)
		return (EXIT_FAILURE);
	if (ft_not_complete(input) == true)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	minishell(char **env)
{
	long		i;
	char		*input;
	t_command	*command;

	(void) env;
	while (g_mysignal == 0)
	{
		//pars_env TO DO
		input = readline("pabloXOC$ ");
		rl_on_new_line();
		if (ft_first_check(input) == EXIT_SUCCESS)
		{
			command = ft_parse_input(input, env);
			add_history(input);
		}
		else
		{
			;
		}
		//parse input TO DO
		//find command TO DO
		if (ft_strncmp(input, "pablo es muy guapo", 19) == 0)
			g_mysignal = 1;
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	minishell(env);
}
