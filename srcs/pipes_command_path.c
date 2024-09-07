/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_command_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:33:45 by ffauth-p          #+#    #+#             */
/*   Updated: 2024/09/04 19:38:23 by paxoc01          ###   ########.fr       */
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

char	*find_command_path(char **envp, char *command, int i, t_data *data)
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
				return (ft_write_error_c(MALLOC_ERROR, data, data->specific[data->sc_pos]));
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
