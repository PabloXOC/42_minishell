/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/07/07 09:08:31 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_dir_env(t_data *data)
{
	if (getcwd(NULL, 500) != NULL)
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
	}
	else
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
	}
	return ;
}

int	home_dir(t_data *data, t_command *full_com)
{
	char	*home_dir;

	home_dir = return_content_var(data->env_lst, "HOME");
	if (home_dir == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (exit_codes(EXIT_2, data));
	}
	else
	{
		if (chdir(home_dir) == -1)
		{
			ft_putstr_fd(full_com->content[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(home_dir, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (exit_codes(EXIT_2, data));
		}
		else
		{
			modify_dir_env(data);
			exit_codes(EXIT_0, data);
		}
	}
	return (exit_codes(EXIT_0, data));
}

int	old_dir(t_data *data, t_command *full_com)
{
	char	*old_dir;

	old_dir = return_content_var(data->env_lst, "OLDPWD");
	if (old_dir == NULL)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (exit_codes(EXIT_2, data));
	}
	else
	{
		if (chdir(old_dir) == -1)
		{
			ft_putstr_fd(full_com->content[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(old_dir, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (exit_codes(EXIT_2, data));
		}
		else
		{
			modify_dir_env(data);
			exit_codes(EXIT_0, data);
		}
	}
	return (exit_codes(EXIT_0, data));
}

int	change_dir(t_data *data, t_command *full_com)
{
	DIR	*new_dir;

	if (full_com->content[1] == NULL)
		return (home_dir(data, full_com));
	else if (ft_strncmp(full_com->content[1], "-", 2) == 0)
		return (old_dir(data, full_com));
	else
	{
		if (chdir(full_com->content[1]) == -1)
		{
			ft_putstr_fd(full_com->content[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(full_com->content[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (exit_codes(EXIT_2, data));
		}
		else
		{
			modify_dir_env(data);
			exit_codes(EXIT_0, data);
		}
	}
	return (exit_codes(EXIT_0, data));
}
