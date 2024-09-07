/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_appearance.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:59:43 by farah             #+#    #+#             */
/*   Updated: 2024/09/04 19:03:25 by paxoc01          ###   ########.fr       */
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

int	refresh_terminal_entry(t_data *data)
{
	int		len_user;
	int		len_dir;
	char	*entry;

	if (data->entry != NULL)
	{
		free(data->entry);
		data->entry = NULL;
	}
	len_user = ft_strlen(data->user);
	len_dir = ft_strlen(data->dir);
	entry = (char *)malloc((len_user + len_dir + 5)); //?
	if (entry == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	ft_memcpy(&entry[0], data->user, len_user);
	ft_memcpy(&entry[len_user], ":", 1);
	ft_memcpy(&entry[len_user + 1], data->dir, len_dir);
	ft_memcpy(&entry[len_user + 1 + len_dir], "$ ", 2);
	entry[len_user + 3 + len_dir] = 0;
	data->entry = entry;
	return (SUCCESS);
}

int	terminal_entry_info(t_data *data, char **env)
{
	if (get_user(data, env) == MALLOC_ERROR
		|| ft_get_dir(data, env) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (SUCCESS);
}
