/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_appearance.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:59:43 by farah             #+#    #+#             */
/*   Updated: 2024/05/04 13:47:12 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_user(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i] != 0)
	{
		if (ft_strncmp(env[i], "LOGNAME=", 7) == 0)
		{
			data->user = ft_strtrim(env[i], "LOGNAME=");
			if (data->user == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
		}
		i++;
	}
	return (SUCCESS);
}

/* int	get_hostname(); */

int	ft_get_dir(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i] != 0)
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			data->dir = ft_strtrim(env[i], "PWD=");
			if (data->dir == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
		}
		i++;
	}
	return (SUCCESS);
}

int	terminal_entry(t_data *data, char **env)
{
	int	len_user;
	int	len_dir;
	int	len_hostname;
	char	*entry;

	if (get_user(data, env) == MALLOC_ERROR || ft_get_dir(data, env) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	len_user = ft_strlen(data->user);
	len_dir = ft_strlen(data->dir);
	len_hostname = ft_strlen("faraway");
	entry = (char *)malloc((len_user + len_dir + len_hostname + 5));
	if (entry == NULL)
		return (MALLOC_ERROR);
	ft_memcpy(&entry[0], data->user, len_user);
	ft_memcpy(&entry[len_user], "@", 1);
	ft_memcpy(&entry[len_user + 1], "faraway", len_hostname);
	ft_memcpy(&entry[len_user + 1 + len_hostname], ":", 1);
	ft_memcpy(&entry[len_user + 2 + len_hostname], data->dir, len_dir);
	ft_memcpy(&entry[len_user + 2 + len_hostname + len_dir], "$ ", 2);
	entry[len_user + 4 + len_hostname + len_dir] = 0;
	data->entry = entry;
	return (SUCCESS);
}
