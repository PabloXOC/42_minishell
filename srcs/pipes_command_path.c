/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_command_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:33:45 by ffauth-p          #+#    #+#             */
/*   Updated: 2024/06/20 15:42:33 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_return_accessible_path(char **available_paths, char *command)
{
	int		i;
	char	*path;
	char	*temp_path;

	i = 0;
	if (available_paths == NULL)
		return (NULL);
	while (available_paths[i] != NULL)
	{
		path = ft_strjoin(available_paths[i], "/");
		if (path == NULL)
			return (NULL);
		temp_path = ft_strjoin(path, command);
		free(path);
		if (temp_path == NULL)
			return (NULL);
		if (access(temp_path, X_OK) == 0)
			return (temp_path);
		free(temp_path);
		i++;
	}
	return (NULL);
}

char	*ft_find_command_path(char **envp, char *command, int i)
{
	char	*temp_path;
	char	**available_paths;

	if (command == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			temp_path = ft_strtrim(envp[i], "PATH=");
			if (temp_path == NULL)
				return (NULL);
			available_paths = ft_split(temp_path, ':');
			free(temp_path);
			temp_path = ft_return_accessible_path(available_paths, command);
			ft_free_char_pp(available_paths);
			if (temp_path == NULL)
				return (ft_strdup(command));
			return (temp_path);
		}
		i++;
	}
	return (NULL);
}

static int	ft_fill_nodes(t_command **node, t_command **head,
	char **command, char *path)
{
	if (command == NULL || path == NULL)
	{
		if (*head != NULL)
			ft_lstclear_com(head, &ft_free_char_pp);
		return (ERROR);
	}
	if (*head != NULL)
	{
		*node = ft_lstnew_com(command);
		ft_lstadd_back_com(head, *node);
	}
	if (*head == NULL)
		*head = ft_lstnew_com(command);
	return (OK);
}

t_command	*ft_fill_commands(char **argv, char **envp, int argc)
{
	t_command	*node;
	t_command	*head;
	int		pos;
	char	**command;
	char	*path;

	pos = 1;
	head = NULL;
	node = NULL;
	while (pos < (argc - 1))
	{
		command = ft_split(argv[pos], 32);
		path = ft_find_command_path(envp, command[0], 0);
		if (ft_fill_nodes(&node, &head, command, path) == ERROR)
			return (NULL);
		pos++;
	}
	return (head);
}

/* t_info	*ft_commands(char **argv, char **envp, int argc)
{
	t_info	*commands;

	commands = (t_info *)malloc(sizeof(t_info));
	if (commands == NULL)
		return (NULL);
	commands->env = envp;
	commands->no_infile = 0;
	commands->no_permissions = 0;
	commands->num_commands = argc - 2;
	commands->temp_file = NULL;
	commands->commands = NULL;
	commands->commands = ft_fill_commands(argv, envp, argc);
	if (commands->commands == NULL)
	{
		perror("Malloc fail");
		ft_free_commands(commands);
		return (NULL);
	}
	return (commands);
} */
