/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_aid2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/09/21 14:30:47 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_create_file_name(t_data *data)
{
	char	*number;
	int		n;

	n = 0;
	while (n >= 0)
	{
		number = ft_itoa(n);
		if (number == NULL)
			return (error_c(MALLOC_ERROR, data, data->spec[data->sc_n]));
		if (ft_file_exists(number) == ERROR)
			return (number);
		n++;
	}
	return (NULL);
}

int	**open_pipes(t_data *data)
{
	int	**pipe_fd;
	int	i;
	int	len_com;

	len_com = ft_lstsize_com(data->spec[data->sc_n]->command_list);
	pipe_fd = (int **) malloc (len_com * sizeof(int *));
	if (pipe_fd == NULL)
		return ((int **)error_c(MALLOC_ERROR, data, data->spec[data->sc_n]));
	i = 0;
	while (i < len_com)
	{
		pipe_fd[i] = (int *)malloc(2 * sizeof(int *));
		if (pipe(pipe_fd[i]) == -1)
		{
			perror("Pipe failure");
			return ((int **) error_c(ERROR, data, data->spec[data->sc_n]));
		}
		i++;
	}
	return (pipe_fd);
}

void	close_pipes(int	**pipe_fd, t_data *data)
{
	int	i;
	int	len_com;

	i = 0;
	len_com = ft_lstsize_com(data->spec[data->sc_n]->command_list);
	while (i < len_com)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		free (pipe_fd[i]);
		i++;
	}
	free (pipe_fd);
	return ;
}
