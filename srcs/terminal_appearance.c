/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_appearance.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:59:43 by farah             #+#    #+#             */
/*   Updated: 2024/05/01 13:20:08 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_user(t_command *command, char **env)
{
	int	i;

	i = 0;
	while (env[i] != 0)
	{
		if (ft_strncmp(env[i], "LOGNAME=", 9) == 0)
		{
			command->user = ft_strtrim(env[i], "LOGNAME=");
			if (command->user == NULL)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

/* int	get_hostname(); */

int	ft_get_dir(t_command *command, char **env)
{
	int	i;

	i = 0;
	while (env[i] != 0)
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			command->dir = ft_strtrim(env[i], "PWD=");
			if (command->dir == NULL)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	terminal_entry(t_command *command, char **env)
{
	int	len_user;
	int	len_dir;
	int	len_hostname;
	char	*entry;

	if (get_user(command, env) == FAILURE || ft_get_dir(command, env) == FAILURE)
		return (FAILURE);
	len_user = ft_strlen(command->user);
	len_dir = ft_strlen(command->dir);
	len_hostname = ft_strlen("faraway");
	entry = (char *)malloc((len_user + len_dir + len_hostname + 5));
	if (entry == NULL)
		return (FAILURE);
	ft_memcpy(&entry[0], command->user, len_user);
	ft_memcpy(&entry[len_user], "@", 1);
	ft_memcpy(&entry[len_user + 1], "faraway", len_hostname);
	ft_memcpy(&entry[len_user + 1 + len_hostname], ":", 1);
	ft_memcpy(&entry[len_user + 2 + len_hostname], command->dir, len_dir);
	ft_memcpy(&entry[len_user + 2 + len_hostname + len_dir], "$ ", 2);
	entry[len_user + 4 + len_hostname + len_dir] = 0;
	command->entry = entry;
	return (SUCCESS);
}
