/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/06/26 16:30:20 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(t_data* data, t_command *full_com)
{
	if (chdir(full_com->content[1]) == -1)
	{
		ft_putstr_fd(full_com->content[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(full_com->content[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		if (data->dir != NULL)
		{
			modify_env(data, "OLDPWD", data->dir);
			free(data->dir);
		}
		data->dir = getcwd(NULL, 500);
		modify_env(data, "PWD", data->dir);
	}
}
