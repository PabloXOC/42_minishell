/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec_coms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/09/21 18:11:05 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	father_process(int **pipe_fd, int i, t_command *com, t_data *data)
{
	int	status;

	if (data->v->fork_id == -1)
	{
		perror("Fork failure");
		return (error_i(ERROR, data));
	}
	if (data->v->fork_id > 0)
	{
		close(pipe_fd[i][1]);
		if (dup2(pipe_fd[i][0], STDIN_FILENO) == -1)
			return (error_i(ERROR, data));
		if (com->next != NULL)
		{
			if (com->next->fd_in > 2)
			{
				if (dup2(com->next->fd_in, STDIN_FILENO) == -1)
					return (error_i(ERROR, data));
			}
		}
		waitpid(data->v->fork_id, &status, 0);
		if (com->previous_error == false)
			exit_codes(WEXITSTATUS(status), data);
	}
	return (SUCCESS);
}

void	exec(t_command *command, t_data *data)
{
	if (execve(command->full_path, command->content, data->env) == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd(command->content[0], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(exit_codes(EXIT_126, data));
		}
		ft_putstr_fd(command->full_path, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(exit_codes(EXIT_127, data));
	}
}

int	pipe_commands(t_command *com, t_data *data, int **pipe_fd, int i)
{
	int	status;

	data->v->fork_id = fork();
	if (father_process(pipe_fd, i, com, data) == MALLOC_ERROR)
		return (error_i(MALLOC_ERROR, data));
	if (data->v->fork_id == 0)
	{
		close(pipe_fd[i][0]);
		if (dup2(pipe_fd[i][1], STDOUT_FILENO) == -1)
			exit(error_i(ERROR, data));
		if (com->fd_out > 2)
			if (dup2(com->fd_out, STDOUT_FILENO) == -1)
				exit(error_i(ERROR, data));
		if (i == ft_lstsize_com(data->spec[data->sc_n]->command_list) - 1
			&& com->fd_out < 2)
			if (dup2(data->v->stdout_cpy, STDOUT_FILENO) == -1)
				exit(error_i(ERROR, data));
		status = find_command(data, com, data->env);
		if (status != ERROR && status != INVALID_COMMAND)
			exit(status);
		if (status == ERROR)
			exit(return_builtin_exit_code(com->content));
		exec(com, data);
	}
	return (SUCCESS);
}

int	restore_original_in_out(t_data *data)
{
	if (dup2(data->v->stdin_cpy, STDIN_FILENO) == -1)
		return (ERROR);
	if (dup2(data->v->stdout_cpy, STDOUT_FILENO) == -1)
		return (ERROR);
	close(data->v->stdin_cpy);
	close(data->v->stdout_cpy);
	return (SUCCESS);
}
