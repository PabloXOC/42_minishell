/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/04/30 14:07:03 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_command(t_command *command, char **env)
{
	char	*com;

	com = command->command_parsed[0];
	if (ft_strncmp(com, "echo", ft_strlen(com)) == 0)
	{
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(com, "cd", ft_strlen(com)) == 0)
	{
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(com, "pwd", ft_strlen(com)) == 0)
	{
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(com, "export", ft_strlen(com)) == 0)
	{
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(com, "unset", ft_strlen(com)) == 0)
	{
		delete_var(command, command->command_parsed[1]);
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(com, "env", ft_strlen(com)) == 0)
		print_char_pp(env);
	if (ft_strncmp(com, "exit", ft_strlen(com)) == 0)
	{
		command->exit = 1;
		return (EXIT_SUCCESS);
	}
}

static int	length_command(t_command *command, int i)
{
	int	len;

	len = 0;
	while (command->command_parsed[i] != NULL && ft_strncmp(command->command_parsed[i], "|", 1) != 0)
	{
		if (ft_strncmp(command->command_parsed[i], "<", 1) == 0)
			i++;
		else if (ft_strncmp(command->command_parsed[i], ">", 1) == 0)
			i++;
		else if (ft_strncmp(command->command_parsed[i], "<<", 2) == 0)
			i++;
		else if (ft_strncmp(command->command_parsed[i], ">>", 2) == 0)
			i++;
		else
			len++;
		i++;
	}
	return (len);
}

static int	write_in_command(t_command *command, int i)
{
	t_list	*com;
	char	**full_command;
	int		pos_command;

	full_command = (char **)malloc((length_command(command, i) + 1)*sizeof(char *));
	if (full_command == NULL)
		return (MALLOC_ERROR);
	full_command[length_command(command, i)] = NULL;
	pos_command = 0;
	while (command->command_parsed[i] != NULL && ft_strncmp(command->command_parsed[i], "|", 1) != 0)
	{
		if (ft_strncmp(command->command_parsed[i], "<", 1) == 0)
			command->redirect_input = command->command_parsed[++i];
		else if (ft_strncmp(command->command_parsed[i], ">", 1) == 0)
			command->redirect_output = command->command_parsed[++i];
		else if (ft_strncmp(command->command_parsed[i], "<<", 2) == 0)
			command->limiter = command->command_parsed[++i];
		else if (ft_strncmp(command->command_parsed[i], ">>", 2) == 0)
			command->append_output = command->command_parsed[++i];
		else
			full_command[pos_command++] = ft_strdup(command->command_parsed[i]);
		if (full_command[pos_command - 1] == NULL)
			return (MALLOC_ERROR);
		i++;
	}
	print_char_pp(full_command);
	com = ft_lstnew(full_command);
	if (com == NULL)
		return (MALLOC_ERROR);
	if (command->command_list != NULL)
		ft_lstadd_back(&command->command_list, com);
	else
		command->command_list = com;
	return (i);
}

void	save_commands(t_command *command)
{
	int	i;

	i = 0;
	while (command->command_parsed[i] != NULL)
	{
		if (i == 0 && ft_strrchr(command->command_parsed[i], '=') != NULL)
			command->create_var = command->command_parsed[i++];
		i = write_in_command(command, i);
		if (command->command_parsed[i] != NULL)
			i++;
	}
}

void	delete_commands(t_command *command)
{
	command->create_var = NULL;
	command->redirect_input = NULL;
	command->redirect_output = NULL;
	command->limiter = NULL;
	command->append_output = NULL;
	ft_lstclear(&command->command_list, &ft_free_char_pp);
	command->command_list = NULL;
}
