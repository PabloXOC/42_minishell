/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/06/26 16:00:35 by marvin            #+#    #+#             */
/*   Updated: 2024/06/26 16:00:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;

/*void catch_sigint_child(int signum)
{
	(void)signum;
	ft_printf("hi");
	if (isatty(STDIN_FILENO))
	{
		write(1, "bro", 3);
		write(STDOUT_FILENO, "\n", 1);
		exit_codes(EXIT_130, NULL);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		kill(0, SIGCHLD);
	}
}*/

void catch_sigint_child(int signum)
{
    (void)signum;
	write(1, "hii", 3);
    exit(exit_codes(EXIT_130, NULL));
}

void	catch_sigint(int signum)
{
	(void)signum;
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "\n", 1);
		exit_codes(EXIT_130, NULL);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*void	catch_sigquit(int signum)
{
	(void)signum;
	write(1, "Quit: 3\n", 8);
	if (!isatty(STDIN_FILENO))
	{
		write(1, "Quit: 3\n", 8);
		exit_codes(EXIT_131, NULL);
		kill(0, SIGCHLD);
	}
}*/

void	catch_sigquit(int signum)
{
	(void)signum;
    write(STDOUT_FILENO, "Quit: 3\n", 8);
    exit(exit_codes(EXIT_131, NULL));
}

int	signal_handle(void)
{
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (SUCCESS);
}
