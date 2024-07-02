/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_aid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/07/02 18:06:56 by farah            ###   ########.fr       */
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
	return (OK);
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
	return (OK);
}

void	close_all_fds(t_command *command)
{
	t_command	*com;

	com = command;
	while (com != NULL)
	{
		if (com->fd_in > 2)
			close(com->fd_in);
		if (com->fd_out > 2)
			close(com->fd_out);
		if (com->temp_file != NULL)
		{
			unlink(com->temp_file);
			free(com->temp_file);
			com->temp_file = NULL;
		}
		com = com->next;
	}
}
