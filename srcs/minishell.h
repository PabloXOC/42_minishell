/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:14:43 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/17 19:18:48 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/*-------INCLUDES-------*/
# include "../libft/ft_printf.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <curses.h>
# include <signal.h>

# define TRUE 1
# define FALSE 0

typedef struct s_command
{
	char	**command_parsed;
	char	*full_address;
}		t_command;

/*------PROTOYPES-------*/
int				main(int argc, char **argv, char **env);

#endif