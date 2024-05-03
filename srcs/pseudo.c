/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:47:15 by paxoc01           #+#    #+#             */
/*   Updated: 2024/05/03 17:07:09 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_errors(command)
{
	//look for multiple tokens in a row
	//check if commands exist && find if correct arguments/flags
	//finding the path of the command
}

int	save_commands(command)
{
	
	
	split_command = split(input, '');
	command = separate_per_command(split_command);  //sep per command and input, output create output files
}

int	main(int argc, char **argv, char **env)
{
	command	*command;

	while (not_ended)
	{
		command->input = recieve_input //first input
		while (input_not_complete(input) == true)
			merge_input(command); //merge      & if << command->user_text = recieve_input();
		save_to_history(input);
		input = reformat(input); //reformat symbols < > |
		
		
		if (check_if_we_save_variables(input) == true) //check =, non-alpha-num, pipes
			save_variables(input) //save variables & edit '\\' & cut string
		save_commands(input);
		check_errors();
	}
}
