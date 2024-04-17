/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/17 13:44:12 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_mysignal;

int	minishell(char **env)
{
	long i;
	char	*input;

	(void) env;
	while (g_mysignal == 0)
	{
		//pars_env TO DO
		input = readline("pabloXOC$ ");
		rl_on_new_line();
		add_history(input);
		//parse input TO DO
		//find command TO DO
		if (ft_strncmp(input, "pablo es muy guapo", 19) == 0)
			g_mysignal = 1;
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	minishell(env);
}

/* int main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;
	char *new_line = "New line content";

	// Read a line of input
	char *input = readline("Enter some text: ");

	// Replace the input line with a new line
	rl_replace_line(new_line, 0);

	// Redisplay the input line with the new content
	rl_redisplay();

	// Free the memory allocated by Readline
	free(input);

	return 0;
} */