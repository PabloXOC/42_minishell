/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/06/20 17:36:20 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	find_command(t_data *data, t_command *full_com, char **env)
{
	char	*com;
	int		len;
	int		len;
	int		len;

	com = full_com->content[0];
	if (ft_strncmp(com, "echo", ft_strlen(com)) == 0)
	{
		//path
		return (SUCCESS);
	}
	if (ft_strncmp(com, "cd", ft_strlen(com)) == 0)
	{
		return (SUCCESS);
	}
	if (ft_strncmp(com, "pwd", ft_strlen(com)) == 0)
	{
		//path
		return (SUCCESS);
	}
	if (ft_strncmp(com, "export", ft_strlen(com)) == 0)
	{
		return (SUCCESS);
	}
	if (ft_strncmp(com, "unset", ft_strlen(com)) == 0)
	{
		delete_var(data, full_com->content[1]);
		return (SUCCESS);
	}
	if (ft_strncmp(com, "env", ft_strlen(com)) == 0)
	{
		//path
		print_char_pp(env);
	}
	if (ft_strncmp(com, "exit", ft_strlen(com)) == 0)
	{
		data->exit = true;
		return (SUCCESS);
	}
	return (INVALID_COMMAND);
} */

static int	len_com(t_data *data, int i)
{
	int	len;

	len = 0;
	while (data->input_info->first_line_split[i] != NULL
		&& ft_strncmp(data->input_info->first_line_split[i], "|", 1) != 0)
	{
		if (ft_strncmp(data->input_info->first_line_split[i], "<", 1) == 0)
			i++;
		else if (ft_strncmp(data->input_info->first_line_split[i], ">", 1) == 0)
			i++;
		else if (ft_strncmp(data->input_info->first_line_split[i], "<<",
				2) == 0)
			i++;
		else if (ft_strncmp(data->input_info->first_line_split[i], ">>",
				2) == 0)
			i++;
		else
			len++;
		i++;
	}
	return (len);
}

/* static int	write_in_command(t_data *data)
{
	t_command	*com;
	char		**full_command;
	int			pos_command;
	int			i;

	i = data->idx_com;
	full_command = (char **)malloc((length_command(data, i) + 1)
			* sizeof(char *));
	if (full_command == NULL)
		return (MALLOC_ERROR);
	full_command[length_command(data, i)] = NULL;
	pos_command = 0;
	while (data->input_info->first_line_split[i] != NULL
		&& ft_strncmp(data->input_info->first_line_split[i], "|", 1) != 0)
	{
		if (ft_strncmp(data->input_info->first_line_split[i], "<", 1) == 0)
		{
			data->redirect_input = data->input_info->first_line_split[++i];
			data->file_input = true;
		}
		else if (ft_strncmp(data->input_info->first_line_split[i], "<<",
				2) == 0)
		{
			data->file_input = false;
		}
		else if (ft_strncmp(data->input_info->first_line_split[i], ">", 1) == 0)
		{
			data->redirect_output = data->input_info->first_line_split[++i];
			data->append_output = false;
		}
		else if (ft_strncmp(data->input_info->first_line_split[i], ">>",
				2) == 0)
		{
			data->redirect_output = data->input_info->first_line_split[++i];
			data->append_output = true;
		}
		else
			full_command[pos_command++] = ft_strdup(data->input_info->first_line_split[i]);
		if (full_command[pos_command - 1] == NULL)
			return (MALLOC_ERROR);
		i++;
	}
	if (data->command_list == NULL)
	{
		data->command_list = ft_lstnew_com(full_command, NULL);
		if (data->command_list == NULL)
			return (MALLOC_ERROR);
	}
	else
	{
		com = ft_lstnew_com(full_command, NULL);
		if (com == NULL)
			return (MALLOC_ERROR);
		ft_lstadd_back_com(&data->command_list, com);
	}
	data->idx_com = i;
	return (SUCCESS);
} */

static int	fill_extra_info(t_data *data, int i, t_command *com)
{
	if (ft_strncmp(data->input_info->first_line_split[i], "<<", 2) == 0)
	{
		com->text_input = data->input_info->first_line_split[++i];
		com->file_input = false;
		return (SUCCESS);
	}
	else if (ft_strncmp(data->input_info->first_line_split[i], "<", 1) == 0)
	{
		com->redirect_input = data->input_info->first_line_split[++i];
		com->file_input = true;
		return (SUCCESS);
	}
	else if (ft_strncmp(data->input_info->first_line_split[i], ">>", 2) == 0)
	{
		com->redirect_output = data->input_info->first_line_split[++i];
		com->append_output = true;
		return (SUCCESS);
	}
	else if (ft_strncmp(data->input_info->first_line_split[i], ">", 1) == 0)
	{
		com->redirect_output = data->input_info->first_line_split[++i];
		com->append_output = false;
		return (SUCCESS);
	}
	return (FAILURE);
}

static int	write_in_command(t_data *data)
{
	t_command	*com;
	char		**full_command;
	int			pos_command;
	int			i;

	i = data->idx_com;
	full_command = (char **)malloc((len_com(data, i) + 1) * sizeof(char *));
	if (full_command == NULL)
		return (MALLOC_ERROR);
	full_command[len_com(data, i)] = NULL;
	com = ft_lstnew_com(full_command);
	if (com == NULL)
		return (MALLOC_ERROR);
	pos_command = 0;
	while (data->input_info->first_line_split[i] != NULL
		&& ft_strncmp(data->input_info->first_line_split[i], "|", 1) != 0)
	{
		if (fill_extra_info(data, i, com) == SUCCESS)
			i++;
		else
		{
			full_command[pos_command++] = ft_strdup(data->input_info->first_line_split[i]);
			if (full_command[pos_command - 1] == NULL)
				return (MALLOC_ERROR);
		}
		i++;
	}
	if (data->command_list == NULL)
		data->command_list = com;
	else
		ft_lstadd_back_com(&data->command_list, com);
	data->idx_com = i;
	return (SUCCESS);
}

void	print_commands(t_data *data)
{
	t_command	*com;

	com = data->command_list;
	while (com != NULL)
	{
		print_char_pp(com->content);
		ft_printf("full path: %s\n", com->full_path);
		ft_printf("text input: %s\n", com->text_input);
		ft_printf("red input: %s\n", com->redirect_input);
		ft_printf("red output: %s\n", com->redirect_output);
		ft_printf("fd in: %i\n", com->fd_in);
		ft_printf("fd out: %i\n", com->fd_out);
		com = com->next;
	}
}

int	save_pipelines(t_data *data)
{
	if (data->input_info->first_line_split == NULL)
		return (0);
	while (data->input_info->first_line_split[data->idx_com] != NULL)
	{
		if (ft_strrchr(data->input_info->first_line_split[data->idx_com],
				'=') != NULL)
			data->idx_com++;
		else
		{
			if (write_in_command(data) != SUCCESS)
				return (FAILURE);
			if (data->input_info->first_line_split[data->idx_com] != NULL)
				data->idx_com++;
		}
	}
	print_commands(data);
	return (SUCCESS);
}

void	delete_commands(t_data *data)
{
	/* data->text_input = NULL;
	data->redirect_input = NULL;
	data->redirect_output = NULL;
	data->file_input = true;
	data->append_output = false; */
	ft_lstclear_com(&data->command_list, &ft_free_char_pp);
	data->command_list = NULL;
	data->idx_com = 0;
}
