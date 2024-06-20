/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/06/18 21:08:40 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	ft_t_clist_clear(t_clist **lst)
{
	t_clist	*next_node;

	while (*lst != NULL)
	{
		next_node = (*lst)->next;
		ft_t_clist_delone(*lst);
		(*lst) = next_node;
	}
}

void	ft_free_commands(t_data *data)
{
	if (data->temp_file != NULL)
		free(data->temp_file);
	if (data->commands != NULL)
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
} */
