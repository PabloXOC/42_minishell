/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec_coms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/07/03 10:36:33 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	father_process(pid_t id, int **pipe_fd, int i, t_command *command, t_data *data)
{
	int	status;

	if (id == -1)
	{
		perror("Fork failure");
		return (ft_write_error_i(ERROR, data));
	}
	if (id > 0)
	{
		close(pipe_fd[i][1]);
		if (dup2(pipe_fd[i][0], STDIN_FILENO) == -1)
			return (ft_write_error_i(ERROR, data));
		if (command->next != NULL)
		{
			if (command->next->fd_in > 2)
			{
				if (dup2(command->next->fd_in, STDIN_FILENO) == -1)
					exit(ft_write_error_i(ERROR, data));
			}
		}
		waitpid(id, &status, 0);
		exit_codes(WEXITSTATUS(status), data);
	}
	return (OK);
}

bool	ft_handle_arg_n(char **command, int n_arg, t_data *data)
{
	int	i;

	i = 0;
	while (command[i] != 0)
		i++;
	if (i == n_arg)
		return (false);
	else
	{
		if (ft_strncmp(command[0], "exit", ft_strlen(command[0])) == 0)
		{
			ft_putstr_fd(command[0], 2);
			ft_putstr_fd(": invalid argument\n", 2);
			exit_codes(EXIT_128, data);
		}
		else
		{
			ft_putstr_fd(command[0], 2);
			ft_putstr_fd(": too many arguments\n", 2);
			exit_codes(EXIT_2, data);
		}
		return (true);
	}
}

bool	ft_check_for_flags(char **command, t_data *data)
{
	if (command[1] == 0)
		return (false);
	else if (command[1][0] == '-')
	{
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd(": no flags accepted for this command\n", 2);
		exit_codes(EXIT_2, data);
		return (true);
	}
	else
		return (false);
}

bool	ft_command_args_errors(char **command, t_data *data)
{
	if (command[0] == NULL)
		return (false);
	if (ft_strncmp(command[0], "echo", ft_strlen(command[0])) == 0)
		return (false);
	if (ft_strncmp(command[0], "pwd", ft_strlen(command[0])) == 0)
		return (ft_check_for_flags(command, data));
	if (ft_strncmp(command[0], "cd", ft_strlen(command[0])) == 0)
	{
		if (command[1] == NULL)
			return (false);
		else if (ft_handle_arg_n(command, 2, data) == false)
			return (false);
		else
			return (true);
	}
	if (ft_strncmp(command[0], "export", ft_strlen(command[0])) == 0)
		return (ft_check_for_flags(command, data));
	if (ft_strncmp(command[0], "unset", ft_strlen(command[0])) == 0)
		return (ft_check_for_flags(command, data));
	if (ft_strncmp(command[0], "env", ft_strlen(command[0])) == 0)
		return (ft_handle_arg_n(command, 1, data));
	if (ft_strncmp(command[0], "exit", ft_strlen(command[0])) == 0)
		return (ft_handle_arg_n(command, 1, data));
	return (false);
}

static int	return_builtin_exit_code(char **command)
{
	if (ft_strncmp(command[0], "exit", ft_strlen(command[0])) == 0)
		return (EXIT_128);
	return (EXIT_2);
}

static void	exec(t_command *command, t_data *data)
{
	if (execve(command->full_path, command->content, data->env) == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd(command->content[0], 2);
			ft_putstr_fd(": command invoked cannot execute\n", 2);
			exit(exit_codes(EXIT_126, data));
		}
		ft_putstr_fd(command->full_path, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(exit_codes(EXIT_127, data));
	}
}

static int	ft_pipe_commands(t_command *command, t_data *data,
	int **pipe_fd, int i)
{
	pid_t	id;

	id = fork();
	if (father_process(id, pipe_fd, i, command, data) == ERROR)
		return (ERROR);
	if (id == 0)
	{
		close(pipe_fd[i][0]);
		if (dup2(pipe_fd[i][1], STDOUT_FILENO) == -1)
			exit(ft_write_error_i(ERROR, data));
		if (command->fd_out > 2)
			if (dup2(command->fd_out, STDOUT_FILENO) == -1)
				exit(ft_write_error_i(ERROR, data));
		if (i == ft_lstsize_com(data->command_list) - 1
			&& command->fd_out < 2)
			if (dup2(data->stdout_cpy, STDOUT_FILENO) == -1)
				exit(ft_write_error_i(ERROR, data));
		if (ft_command_args_errors(command->content, data) == true)
			exit(return_builtin_exit_code(command->content));
		if (find_command(data, command, data->env) == SUCCESS)
			exit(0);
		exec(command, data);
	}
	return (OK);
}

static int	restore_original_in_out(t_data *data)
{
	if (dup2(data->stdin_cpy, STDIN_FILENO) == -1)
		return (ERROR);
	if (dup2(data->stdout_cpy, STDOUT_FILENO) == -1)
		return (ERROR);
	close(data->stdin_cpy);
	close(data->stdout_cpy);
	return (SUCCESS);
}
static int	refresh_content_com(t_command *com, t_data *data)
{
	int	i;

	i = 0;
	if (refresh_mysignal_var(data) == MALLOC_ERROR)
		return (ERROR);
	while (com->content[i] != NULL)
	{
		com->content[i] = expand_var(data, com->content[i]);
		if (com->content[i] == NULL)
			return (ERROR);
		i++;
	}
	com->full_path = ft_find_command_path(data->env, com->content[0], 0, data);
	if (data->fatal_error == true)
		return (ERROR);
	return (SUCCESS);
}

int	pipe_exec_coms(t_data *data)
{
	int			**pipe_fd;
	t_command	*com;
	int			i;

	data->stdin_cpy = dup(STDIN_FILENO);
	data->stdout_cpy = dup(STDOUT_FILENO);
	com = data->command_list;
	pipe_fd = open_pipes(data);
	if (pipe_fd == NULL)
		return (ERROR);
	dup2(com->fd_in, STDIN_FILENO);
	i = 0;
	if (refresh_content_com(com, data) == ERROR)
		return (ERROR);
	if (ft_pipe_commands(com, data, pipe_fd, i++) == ERROR)
		return (ERROR);
	com = com->next;
	while (com != NULL)
	{
		if (refresh_content_com(com, data) == ERROR)
			return (ERROR);
		if (ft_pipe_commands(com, data, pipe_fd, i++) == ERROR)
			return (ERROR);
		com = com->next;
	}
	close_pipes(pipe_fd, data);
	return (restore_original_in_out(data));
}

int	exec_commands(t_data *data)
{
	int	list_len;

	list_len = ft_lstsize_com(data->command_list);
	if (list_len == 1)
	{
		if (ft_command_args_errors(data->command_list->content, data) == true)
			return (SUCCESS);
		if (find_command(data, data->command_list, data->env)
			== INVALID_COMMAND && data->fatal_error == false)
			return (pipe_exec_coms(data));
		g_exit_status = 0;
	}
	if (list_len > 1)
		return (pipe_exec_coms(data));
	return (SUCCESS);
}
