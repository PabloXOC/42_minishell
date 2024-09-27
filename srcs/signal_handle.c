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

/* void	handle_sigint(int sig)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	//rl_done = 1;
	exit_codes(EXIT_130, NULL);
} */

//control c
/* void	catch_sigint(int signum)
{
	(void)signum;
	kill(0, SIGCHLD);
	exit_codes(EXIT_130, NULL);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
} */

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

//control bar

/* void	catch_sigquit(int signum)
{
	(void)signum;
	printf("Quit: 3\n");
	exit_codes(EXIT_131, NULL);
	kill(0, SIGCHLD);
} */

void	catch_sigquit(int signum)
{
	(void)signum;
	if (!isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "Quit: 3\n", 8);
		exit_codes(EXIT_131, NULL);
		kill(0, SIGCHLD);
	}
}

int	signal_handle(void)
{
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (SUCCESS);
}

/* int	signal_handle(void)
{
	struct sigaction	sa;
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, catch_sigquit);
	sa.sa_handler = catch_sigint;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (FAILURE);
	}
	signal(SIGQUIT, SIG_IGN);
	return (SUCCESS);
} */
