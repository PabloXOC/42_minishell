/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_aid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/06/20 17:28:28 by ffauth-p         ###   ########.fr       */
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
	{
		perror("Open failure");
		return (ERROR);
	}
	commands->fd_in = fd;
	return (OK);
}

int	ft_open_outfile(char *file, t_command *commands)
{
	int		fd;

	if (commands->append_output == false)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Open failure");
		return (ERROR);
	}
	commands->fd_out = fd;
	return (OK);
}

int	ft_file_permissions(t_command *command)
{
	t_command	*com;
	int			status;

	com = command;
	status = SUCCESS;
	while (com != NULL)
	{
		if (com->redirect_input != NULL) //also put input file for terminal input
			if (ft_infile_permissions(com->redirect_input, com) == ERROR)
				status = ERROR;
		if (com->redirect_output != NULL)
			if (ft_outfile_permissions(com->redirect_output, com) == ERROR)
				status = ERROR;
		com = com->next;
	}
	return (status);
}
