/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aid2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/05/29 14:58:08 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include "pipex.h"

int	ft_file_permissions(char *file1, char *file2, t_info *commands)
{
	if (ft_infile_permissions(file1, commands) == ERROR
		|| ft_outfile_permissions(file2, commands) == ERROR)
		return (ERROR);
	return (OK);
}

char	*ft_create_file_name(void)
{
	char	*number;
	int		n;

	n = 0;
	while (n >= 0)
	{
		number = ft_itoa(n);
		if (ft_file_exists(number) == ERROR)
			return (number);
		n++;
	}
	return (NULL);
}

int	**open_pipes(t_info *commands)
{
	int	**pipe_fd;
	int	i;

	pipe_fd = (int **) malloc (commands->num_commands * sizeof(int *));
	if (pipe_fd == NULL)
		return (NULL);
	i = 0;
	while (i < commands->num_commands)
	{
		pipe_fd[i] = (int *)malloc(2 * sizeof(int *));
		if (pipe(pipe_fd[i]) == -1)
		{
			perror("Pipe failure");
			return (NULL);
		}
		i++;
	}
	return (pipe_fd);
}

void	close_pipes(int	**pipe_fd, t_info *commands)
{
	int	i;

	i = 0;
	while (i < commands->num_commands)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		free (pipe_fd[i]);
		i++;
	}
	free (pipe_fd);
	return ;
}
