/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:50:44 by farah             #+#    #+#             */
/*   Updated: 2024/05/29 14:36:00 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "libft/libft.h"
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_info	*commands;

	if (argc >= 5)
	{
		argv++;
		argc--;
		commands = ft_commands(argv, envp, argc);
		if (commands == NULL)
			return (1);
		if (ft_file_permissions(argv[0], argv[argc - 1], commands) == ERROR)
		{
			ft_cleanup(argv[0], commands);
			return (1);
		}
		if (ft_bonus_father_child(commands) == ERROR)
		{
			ft_cleanup(argv[0], commands);
			return (1);
		}
		ft_cleanup(argv[0], commands);
		return (0);
	}
	ft_putstr_fd("Input error\n", 2);
	return (1);
}
