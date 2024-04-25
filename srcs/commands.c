/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/04/25 19:39:14 by farah            ###   ########.fr       */
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
