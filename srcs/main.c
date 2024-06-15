/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/15 17:32:00 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_mysignal = 0;

/* int	check_errors(command)
{
	//look for multiple tokens in a row
	//check if commands exist && find if correct arguments/flags
	//finding the path of the command
} */
/* 
char	*ft_join_path_command(char *command, char **paths, int i)
{
	char	*str;
	char	*str2;

	str = ft_strjoin(paths[i], "/");
	if (!(str))
		return (ft_write_error_c(MALLOC_ERROR, command));
	str2 = ft_strjoin(str, command);
	free(str);
	if (!(str2))
		return (ft_write_error_c(MALLOC_ERROR, command));
	return (str2);
}

char	*ft_full_command(t_data *data, char **paths)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i] != 0)
	{
		full_path = ft_join_path_command(data->input_split[0], paths, i);
		if (full_path == NULL)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
 */

/* int	ft_parse_input(t_data *data, char **env)
{
	char		**paths;
	int			i;

	i = 0;
	data->input_split = ft_split(data->input, ' ');
	if (data->input_split == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	if (ft_correct_input(data->input_split[0]) == FAILURE)
		return (FAILURE);
	while (env[i] != 0)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(ft_strchr(env[i], '/'), ':');
			if (paths == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
			break ;
		}
		i++;
	}
	data->full_address = ft_full_command(data, paths);
	printf("Command: %s\n", data->full_address);
	return (SUCCESS);
} */


char	*ft_user_text(char *eof, t_data *data)
{
	char	*input;
	char	*user_text;

	user_text = NULL;
	while (42)
	{
		input = readline("> ");
		if (ft_samestr(input, eof) == true)
			return (user_text);
		user_text = ft_strjoin(user_text, input);
	}
}

/* //multiple << are possible
int	get_text_input(t_data *data)
{
	
} */

void	ft_free_char_star_star(char **list)
{
	int	i;

	i = 0;
	if (list != NULL)
	{
		while (list[i] != 0)
		{
			if (list[i] != NULL)
				free(list[i]);
			i++;
		}
		free(list);
	}
}

void	ft_free_input_info(t_data *data)
{
	if (data->input_info != NULL)
	{
		if (data->input_info->final_text != NULL)
			free(data->input_info->final_text);
		if (data->input_info->first_line != NULL)
			free(data->input_info->first_line);
		if (data->input_info->first_line_and_final_text != NULL)
			free(data->input_info->first_line_and_final_text);
		if (data->input_info->first_line_ref != NULL)
			free(data->input_info->first_line_ref);
		if (data->input_info->first_line_split != NULL)
			free(data->input_info->first_line_split);
		if (data->input_info->init_input != NULL)
			free(data->input_info->init_input);
		if (data->input_info->init_input_split != NULL)
			free(data->input_info->init_input_split);
		ft_free_char_star_star(data->input_info->list_eof);
		if (data->input_info->terminal_input != NULL)
			free(data->input_info->terminal_input);
		free(data->input_info);
	}
	data->input_info = NULL;
}

int	minishell(char **env)
{
	t_data	*data;

	data = data_init();
	if (data == NULL)
		return (MALLOC_ERROR);
	terminal_entry(data, env);
	while (g_mysignal == 0 && data->malloc_error == false
		&& data->exit == false) //find more reasons to break
	{
		//data->input = readline(data->entry);
		if (recieve_complete_input(data) == SUCCESS)
		{
			add_history(data->input_info->first_line_and_final_text);
			//data->input = ft_reformat_input(data->input, data); // reformat and split input (not \\)
			data->input_info->first_line_split = ft_minishell_split(data->input_info->first_line_ref, ' ');
			if (data->input_info->first_line_split == NULL)
				return (ft_write_error_i(MALLOC_ERROR, data));
			if (data->malloc_error == true)
				return (MALLOC_ERROR);
			if (check_if_we_save_variables(data) == true)
				save_variables(data); // TO DO edit '\\' & cut string
			if (data->malloc_error == true)
				return (MALLOC_ERROR);
			//open files (maybe after commands)
			if (save_commands(data) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			//find_command(command, env);
			//execute_commands(data); //TO DO LATER
			//delete_commands(data);
		}
		ft_free_input_info(data);// TO DO free stuff
	}
	// TO DO free even more stuff
	rl_clear_history();
	return (EXIT_SUCCESS);
}


//what happens when export? do we save_variables or execute_commands


int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	//int	tok;
	//char str[] = "hello my name << \'>> >> >\' << is >>  pablo < a";
	//char str[] = "hi << \"<<\"  feos todos << viva españa";
	t_data	*data;;

	if (minishell(env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	/* data = data_init();
	if (data == NULL)
		return (MALLOC_ERROR);
	data->first_line_ref = str;
	data->n_eof = 2;
	tok = ft_check_token(data);
	if (tok == 0)
	{
		ft_ter_input(data, 0, 0, 0);
		ft_save_until_eof(data);
		ft_printf("FINAL:%sAAA\n", data->final_text);
	}
	else
	{
		ft_printf("TOK: %d\n", tok);
	}
	 */
	//recieve_complete_input(data);
}
