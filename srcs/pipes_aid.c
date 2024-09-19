/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_aid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/09/19 15:23:18 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_char_pp_len(char **stack)
{
	int	i;

	i = 0;
	while (stack[i] != NULL)
		i++;
	return (i);
}

int	ft_open_infile(char *file, t_command *commands)
{
	int		fd;

	fd = open(file, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
		return (ERROR);
	commands->fd_in = fd;
	return (SUCCESS);
}

int	ft_open_outfile(char *file, t_command *commands)
{
	int		fd;

	if (commands->append_output == false)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (ERROR);
	commands->fd_out = fd;
	return (SUCCESS);
}


