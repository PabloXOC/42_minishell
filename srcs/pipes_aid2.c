/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_aid2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/07/02 18:56:56 by farah            ###   ########.fr       */
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
			return (ft_write_error_c(MALLOC_ERROR, data));
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

	len_com = ft_lstsize_com(data->command_list);
	pipe_fd = (int **) malloc (len_com * sizeof(int *));
	if (pipe_fd == NULL)
		return ((int **) ft_write_error_c(MALLOC_ERROR, data));
	i = 0;
	while (i < len_com)
	{
		pipe_fd[i] = (int *)malloc(2 * sizeof(int *));
		if (pipe(pipe_fd[i]) == -1)
		{
			perror("Pipe failure");
			return ((int **) ft_write_error_c(ERROR, data));
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
	len_com = ft_lstsize_com(data->command_list);
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
