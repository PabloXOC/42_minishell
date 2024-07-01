/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/07/01 12:39:57 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_dir_env(t_data *data)
{
	if (data->dir != NULL)
	{
		modify_env(data, "OLDPWD", data->dir);
		modify_export(data, "OLDPWD", data->dir);
		free(data->dir);
	}
	data->dir = getcwd(NULL, 500);
	modify_env(data, "PWD", data->dir);
	modify_export(data, "PWD", data->dir);
	return ;
}

void	home_dir(t_data *data, t_command *full_com)
{
	char	*home_dir;

	home_dir = return_content_var(data->env_lst, "HOME");
	if (home_dir == NULL)
		ft_putstr_fd("cd: HOME not set\n", 2);
	else
	{
		if (chdir(home_dir) == -1)
		{
			ft_putstr_fd(full_com->content[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(home_dir, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
			modify_dir_env(data);
	}
	return ;
}

void	change_dir(t_data *data, t_command *full_com)
{
	if (full_com->content[1] == NULL)
		home_dir(data, full_com);
	else
	{
		if (chdir(full_com->content[1]) == -1)
		{
			ft_putstr_fd(full_com->content[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(full_com->content[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
			modify_dir_env(data);
	}
	return ;
}
