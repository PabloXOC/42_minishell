/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_aid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/06/18 21:41:46 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	ft_free_char_pp(char **stack)
{
	int	i;

	i = 0;
	while (stack[i] != NULL)
	{
		free(stack[i]);
		i++;
	}
	free (stack);
} */

int	ft_char_pp_len(char **stack)
{
	int	i;

	i = 0;
	while (stack[i] != NULL)
		i++;
	return (i);
}

/* void	print_char_pp(char **stack)
{
	int	i;

	i = 0;
	while (stack[i] != NULL)
	{
		ft_printf("%s\n", stack[i]);
		i++;
	}
} */

/* int	ft_open_infile(char *file, t_info *commands)
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

int	ft_open_outfile(char *file, t_info *commands)
{
	int		fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Open failure");
		return (ERROR);
	}
	commands->fd_out = fd;
	return (OK);
} */
