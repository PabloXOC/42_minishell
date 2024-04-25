/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/18 11:49:32 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_mysignal;

int	ft_samestr(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (EXIT_FAILURE);
	while (s1[i])
	{
		if (s1[i] - s2[i] != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

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
		add_history(input);
		command = ft_parse_input(input, env);
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

/* int main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;
	char *new_line = "New line content";

	// Read a line of input
	char *input = readline("Enter some text: ");

	// Replace the input line with a new line
	rl_replace_line(new_line, 0);

	// Redisplay the input line with the new content
	rl_redisplay();

	// Free the memory allocated by Readline
	free(input);

	return 0;
} */