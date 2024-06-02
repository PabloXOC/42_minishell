/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/05/29 14:58:43 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "libft/libft.h"
#include "pipex.h"

static int	father_process(pid_t id, int **pipe_fd, int i)
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

static int	ft_pipe_commands(t_clist *command, t_info *commands,
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
		if (i == commands->num_commands - 1)
		{
			if (dup2(commands->fd_out, STDOUT_FILENO) == -1)
				exit(ERROR);
		}
		if (execve(command->path, command->command, commands->env) == -1)
		{
			ft_putstr_fd(command->path, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
	return (OK);
}

int	ft_bonus_father_child(t_info *commands)
{
	int		**pipe_fd;
	t_clist	*com;
	int		i;

	com = commands->commands;
	pipe_fd = open_pipes(commands);
	if (pipe_fd == NULL)
		return (ERROR);
	dup2(commands->fd_in, STDIN_FILENO);
	i = 0;
	if (ft_pipe_commands(com, commands, pipe_fd, i++) == ERROR)
		return (ERROR);
	com = com->next;
	while (com->next != NULL)
	{
		if (ft_pipe_commands(com, commands, pipe_fd, i++) == ERROR)
			return (ERROR);
		com = com->next;
	}
	if (ft_pipe_commands(com, commands, pipe_fd, i++) == ERROR)
		return (ERROR);
	/* if (execve(com->path, com->command, commands->env) == -1)
	{
		ft_putstr_fd(com->path, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	} */
	close_pipes(pipe_fd, commands);
	return (OK);
}
