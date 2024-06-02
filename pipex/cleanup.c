/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/05/29 15:06:51 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include "pipex.h"

void	ft_t_clist_clear(t_clist **lst)
{
	t_clist	*next_node;

	while (*lst != NULL)
	{
		next_node = (*lst)->next;
		ft_t_clist_delone(*lst);
		(*lst) = next_node;
	}
}

void	ft_free_commands(t_info *commands)
{
	if (commands->temp_file != NULL)
		free(commands->temp_file);
	if (commands->commands != NULL)
		ft_t_clist_clear(&(commands->commands));
	if (commands != NULL)
		free(commands);
}

void	ft_cleanup(char *in_file, t_info *commands)
{
	close(commands->fd_in);
	close(commands->fd_out);
	if (commands->no_infile == 1)
		unlink(in_file);
	if (commands->no_permissions == 1)
		unlink(commands->temp_file);
	ft_free_commands(commands);
}
