/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:00:35 by marvin            #+#    #+#             */
/*   Updated: 2024/06/26 16:00:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

void	handle_sigint(int sig)
{
    ft_putchar_fd('\n', STDOUT_FILENO);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    g_exit_status = 130;
}

int	signal_handle()
{
	struct sigaction sa;
	
    // Configurar el manejador para SIGINT (Ctrl-C)
	sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1)
	{
        perror("sigaction");
        return (FAILURE);
    }
    // Configurar el manejador para SIGQUIT (Ctrl-\)
    signal(SIGQUIT, SIG_IGN);
	return (SUCCESS);
}
