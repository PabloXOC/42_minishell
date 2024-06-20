/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec_coms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/06/20 15:51:26 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int	father_process(pid_t id, int **pipe_fd, int i)
{
	if (id == -1)
	{
		perror("Fork failure");
		return (ERROR);
	}
	if (id > 0)
	{
		close(pipe_fd[i][1]);
		if (dup2(pipe_fd[i][0], STDIN_FILENO) == -1)
			return (ERROR);
		waitpid(id, NULL, 0);
	}
	return (OK);
}

static int	ft_pipe_commands(t_command *command, t_data *data,
	int **pipe_fd, int i)
{
	pid_t	id;

	id = fork();
	if (father_process(id, pipe_fd, i) == ERROR)
		return (ERROR);
	if (id == 0)
	{
		close(pipe_fd[i][0]);
		if (dup2(pipe_fd[i][1], STDOUT_FILENO) == -1)
			exit(ERROR);
		if (i == ft_lstsize_com(data->command_list) - 1)
		{
			if (dup2(data->fd_out, STDOUT_FILENO) == -1)
				exit(ERROR);
		}
		if (execve(command->full_path, command->content, data->env) == -1)
		{
			ft_putstr_fd(command->full_path, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
	return (OK);
}

int	pipe_exec_coms(t_data *data)
{
	int			**pipe_fd;
	t_command	*com;
	int			i;

	com = data->command_list;
	pipe_fd = open_pipes(data);
	if (pipe_fd == NULL)
		return (ERROR);
	dup2(data->fd_in, STDIN_FILENO);
	i = 0;
	if (ft_pipe_commands(com, data, pipe_fd, i++) == ERROR)
		return (ERROR);
	com = com->next;
	while (com->next != NULL)
	{
		if (ft_pipe_commands(com, data, pipe_fd, i++) == ERROR)
			return (ERROR);
		com = com->next;
	}
	if (ft_pipe_commands(com, data, pipe_fd, i++) == ERROR)
		return (ERROR);
	close_pipes(pipe_fd, data);
	return (OK);
} */
